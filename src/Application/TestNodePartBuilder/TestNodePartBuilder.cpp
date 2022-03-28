/*
 * reference LICENSE file provided.
 *
 * TestNodePartBuilder.cpp.
 *
 * Implements TestNodePartBuilder.hpp.
 *
 */

#include <iostream>
#include <string>

#include <NodePartBuilder/inPs.hpp>
#include <NodePartBuilder/outPs.hpp>
#include <NodePartBuilder/genPs.hpp>
#include <NodePartBuilder/procPs.hpp>
#include <NodePartBuilder/dispPs.hpp>

#include <NodePart/OutputPipe/OutputPipeFile.hpp>
#include <NodePart/InputPipe/InputPipeFile.hpp>
#include <NodePart/Generator/GeneratorSine.hpp>
#include <NodePart/Display/DisplayFile.hpp>
#include <NodePart/Processor/ProcessorDc.hpp>

#include "TestNodePartBuilder.hpp"

void Test_inPs_outPs()
{
  // initialize pointers.
  //
  OutputPipeBase* my_outFile = nullptr;
  InputPipeBase* my_inFile = nullptr;

  // instantiate concrete types.
  //
  outFilePs my_outFilePs(std::string("Test_inPs_outPs.txt"));
  inFilePs my_inFilePs(std::string("Test_inPs_outPs.txt"));

  // assign abstract pointer types.
  //
  outPs* my_outPs = &my_outFilePs;
  inPs* my_inPs = &my_inFilePs;

  // test 'Make' with concrete types.
  //
  my_outFile = my_outFilePs.Make();
  my_inFile = my_inFilePs.Make();
  std::cout << "outFilePs::Make: " << (my_outFile != nullptr ? "OK" : "BAD")
    << std::endl;
  std::cout << "inFilePs::Make: " << (my_inFile != nullptr ? "OK" : "BAD")
    << std::endl;

  delete my_outFile;
  my_outFile = nullptr;
  delete my_inFile;
  my_inFile = nullptr;

  my_outFile = my_outPs->Make();
  my_inFile = my_inPs->Make();
  std::cout << "outPs::Make: " << (my_outFile != nullptr ? "OK" : "BAD")
    << std::endl;
  std::cout << "inPs::Make: " << (my_inFile != nullptr ? "OK" : "BAD")
    << std::endl;

  delete my_inFile;
  my_inFile = nullptr;
  delete my_outFile;
  my_outFile = nullptr;
}

void Test_genPs()
{
  genSinePs<double> my_genSinePs(0.0, 0.0, 0.0, 0.0, 1000);
  genPs<double>* my_genPs = &my_genSinePs;
  GeneratorBase<double>* my_GeneratorSine = nullptr;

  my_GeneratorSine = my_genSinePs.Make();
  std::cout << "genSinePs::Make: " << (my_GeneratorSine != nullptr ?
    "OK" : "BAD")
    << std::endl;

  delete my_GeneratorSine;
  my_GeneratorSine = nullptr;

  my_GeneratorSine = my_genPs->Make();
  std::cout << "genPs::Make: " << (my_GeneratorSine != nullptr ? 
    "OK" : "BAD")
    << std::endl;

  delete my_GeneratorSine;
  my_GeneratorSine = nullptr;
}

void Test_procPs()
{
  procDcPs<double, double> my_procDcPs(-10.5);
  procPs<double, double>* my_procPs = &my_procDcPs;
  ProcessorBase<double, double>* my_ProcessorDc = nullptr;

  my_ProcessorDc = my_procDcPs.Make();
  std::cout << "procDcPs::Make: " << (my_ProcessorDc != nullptr ?
    "OK" : "BAD")
    << std::endl;

  delete my_ProcessorDc;
  my_ProcessorDc = nullptr;

  my_ProcessorDc = my_procPs->Make();
  std::cout << "procPs::Make: " << (my_ProcessorDc != nullptr ? 
    "OK" : "BAD")
    << std::endl;

  delete my_ProcessorDc;
  my_ProcessorDc = nullptr;
}

void Test_dispPs()
{
  dispFilePs<int> my_dispFilePs(std::string("Test_dispPs.txt"));
  dispPs<int>* my_dispPs = &my_dispFilePs;
  DisplayBase<int>* my_DisplayFile = nullptr;

  my_DisplayFile = my_dispFilePs.Make();
  std::cout << "dispFilePs::Make: " << (my_DisplayFile != nullptr ?
    "OK" : "BAD")
    << std::endl;

  delete my_DisplayFile;
  my_DisplayFile = nullptr;

  my_DisplayFile = my_dispPs->Make();
  std::cout << "dispPs::Make: " << (my_DisplayFile != nullptr ? 
    "OK" : "BAD")
    << std::endl;

  delete my_DisplayFile;
  my_DisplayFile = nullptr;
}

void TestNodePartBuilder()
{
  Test_inPs_outPs();
  Test_genPs();
  Test_procPs();
  Test_dispPs();
}

