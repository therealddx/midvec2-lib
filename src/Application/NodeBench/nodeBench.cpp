#include "nodeBench.hpp"

void printBadArgs()
{
  std::cout << "nodebench: bad usage: read usage (`nodebench`)"
    << std::endl;
}

void printUsage()
{
  std::cout
    << "nodebench: usage:" << std::endl
    << "  nodebench [ [ NODE-TYPE ] [ NODE-PART ] ] ..." << std::endl
    << ""
    << "    [ NODE-TYPE ] is any of: byte-node source-node show-node core-node mixer-node" << std::endl
    << "    [ NODE-PART ] is any of: INPUT-PIPE OUTPUT-PIPE GENERATOR DISPLAY PROCESSOR" << std::endl
    << std::endl
    << ""
    << "  each NODE-TYPE is constructed as:"                                << std::endl
    << "    byte-node   [ INPUT-PIPE ] [ OUTPUT-PIPE ]"                     << std::endl
    << "    source-node [ GENERATOR ]  [ OUTPUT-PIPE ]"                     << std::endl
    << "    show-node   [ INPUT-PIPE ] [ DISPLAY ]"                         << std::endl
    << "    core-node   [ INPUT-PIPE ] [ PROCESSOR ] [ OUTPUT-PIPE ]"       << std::endl
    << "    mixer-node  [ INPUT-PIPE-1 ] [ INPUT-PIPE-2 ] [ OUTPUT-PIPE ] " << std::endl
    << std::endl
    << ""
    << "  INPUT-PIPE is constructed as:"                                           << std::endl
    << "    InputPipeRam  : [ --input-pipe-ram | -ipr ] [ rb-uid ]"                << std::endl
    << "    note:"                                                                 << std::endl
    << "      'rb-uid' is the UID for the ringbuffer this InputPipeRam reads from" << std::endl
    << "    OR," << std::endl
    << "    InputPipeFile : [ --input-pipe-file | -ipf ] [ file-uid ]"             << std::endl
    << "    note:"                                                                 << std::endl
    << "      files will be read from disk as 'nodebench-file<file-uid>.dat'"      << std::endl
    << "" << std::endl
    << ""
    << "  OUTPUT-PIPE is constructed as:"                                          << std::endl
    << "    OutputPipeRam  : [ --output-pipe-ram | -opr ] [ rb-uid ]"              << std::endl
    << "    note:"                                                                 << std::endl
    << "      'rb-uid' is the UID for the ringbuffer this OutputPipeRam writes to" << std::endl
    << "    OR," << std::endl
    << "    OutputPipeFile : [ --output-pipe-file | -opf ] [ file-uid ]"           << std::endl
    << "    note:"                                                                 << std::endl
    << "      files will be written to disk as 'nodebench-file<file-uid>.dat'"     << std::endl
    << "" << std::endl
    << ""
    << "  GENERATOR is constructed as:"                                            << std::endl
    << "    GeneratorSine:"                                                        << std::endl
    << "      [ --generator-sine | -gsine ] [ x-shift ] [ x-scale ]"               << std::endl
    << "        [ y-shift ] [ y-scale ] [ samples/period ]"                        << std::endl
    << "    OR," << std::endl
    << "    GeneratorSquare:"                                                      << std::endl
    << "      [ --generator-square | -gsquare ] [ x-shift ] [ x-scale ]"           << std::endl
    << "        [ y-shift ] [ y-scale ] [ samples/period ]"                        << std::endl
    << "" << std::endl
    << ""
    << "  DISPLAY is constructed as:"                                              << std::endl
    << "    DisplayFile:"                                                          << std::endl
    << "      [ --display-file | -dfile ] [ filename ]"                            << std::endl
    << "" << std::endl
    << ""
    << "  PROCESSOR is constructed as:"                                            << std::endl
    << "    ProcessorDc   : [ --processor-dc | -pdc ] [ dc-bias ]"                 << std::endl
    << "    OR," << std::endl
    << "    ProcessorConv : [ --processor-conv | -pconv ] [ fir-filename ]"        << std::endl
    << "    note:" << std::endl
    << "      the ProcessorConv's h[n] will be read as whitespace-delimited"       << std::endl
    << "      doubles from <fir-filename>."                                        << std::endl
    << ""
    << ""
    << ""
    << "" << std::endl;
}

bool midv_parse_int(char* arg_cstring, int32_t& rtn_int)
{
  int32_t num_values_parsed = sscanf(arg_cstring, "%d", &rtn_int);
  return num_values_parsed == 1;
}

bool midv_parse_double(char* arg_cstring, double& rtn_double)
{
  int32_t num_values_parsed = sscanf(arg_cstring, "%lf", &rtn_double);
  return num_values_parsed == 1;
}

