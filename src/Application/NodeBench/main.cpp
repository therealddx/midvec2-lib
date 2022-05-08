/**
 * reference LICENSE file provided.
 *
 * main.cpp
 * Entry point for nodebench test application.
 *
 */

#include "stdinclude.hpp" 
#include "nodeBench.hpp"
#include "BenchLog.hpp"
#include <Node/IStorableNode.hpp>
#include <NodeBuilder/nodePs.hpp>
#include <NodePartBuilder/inPs.hpp>
#include <NodePartBuilder/outPs.hpp>
#include <NodePartBuilder/genPs.hpp>
#include <NodePartBuilder/procPs.hpp>

#include "main.hpp"

// gl_error_main
//   error across the entirety of the application's execution.
//   '0' => application ended as intended by both user and coder.
//   '1' => not the above.
//
int32_t gl_error_main = 0;

RingBuffer<char>* make_RingBuffer()
{
  return new RingBuffer<char>(1024, 512, false);
}

dispPs<double>* dispPs_from_cli(char** argv_offset)
{
  if (!strcmp("-dfile", *argv_offset) || !strcmp("--display-file", *argv_offset))
  {
    return new dispFilePs<double>( *(argv_offset + 1) );
  }
  else
  {
    return nullptr;
  }
}

procPs<double, double>* procPs_from_cli(char** argv_offset)
{
  // vars.
  procPs<double, double>* rtn_processor_paramset;
  double dc_offset;
  std::vector<double> hn;

  // parse in the 'PROCESSOR' from the CLI.
  //
  if ( !strcmp("-pdc", *argv_offset)
    || !strcmp("--processor-dc", *argv_offset))
  {
    bool parse_dc_ok = midv_parse_double( *(argv_offset + 1), dc_offset);
    if (parse_dc_ok)
      { rtn_processor_paramset = new procDcPs<double, double>(dc_offset); }
    else
      { return nullptr; }
  }
  else if
     ( !strcmp("-pconv", *argv_offset)
    || !strcmp("--processor-conv", *argv_offset))
  {
    std::ifstream f_hn_ssv( *(argv_offset + 1) );

    if (!f_hn_ssv.is_open())
      { return nullptr; }

    // parse in the h[n] component values.
    //   can merely cleanup and `return nullptr` if error.
    //
    while (!f_hn_ssv.eof())
    {
      double new_value;
      f_hn_ssv >> new_value;

      if (f_hn_ssv.bad())
      {
        f_hn_ssv.close();
        return nullptr;
      }

      if (f_hn_ssv.eof())
      {
        f_hn_ssv.close();
        break;
      }

      hn.push_back(new_value);
    }

    // report.
    //
    std::cout << "nodebench: found impulse response ('"
      << hn.size() << "' elements): " << std::endl << "  ";

    for (auto each : hn)
      { std::cout << each << " "; }
    std::cout << std::endl;

    // assign.
    rtn_processor_paramset = new procConvPs<double, double>(hn);
  }
  else
  {
    return nullptr;
  }

  // ret.
  return rtn_processor_paramset;
}

genPs<double>* genPs_from_cli(char** argv_offset)
{
  // vars.
  genPs<double>* rtn_generator_paramset = nullptr;
  double x_shift = 0.0;
  double x_scale = 0.0;
  double y_shift = 0.0;
  double y_scale = 0.0;
  int32_t samps_per = 0;

  // parse in the x/y shift/scale.
  //
  if ( !midv_parse_double( *(argv_offset + 1), x_shift)
    || !midv_parse_double( *(argv_offset + 2), x_scale)
    || !midv_parse_double( *(argv_offset + 3), y_shift)
    || !midv_parse_double( *(argv_offset + 4), y_scale)
    || !midv_parse_int   ( *(argv_offset + 5), samps_per))
  {
    return nullptr;
  }

  // construct the corresponding 'genPs'.
  //
  if ( !strcmp("-gsine", *argv_offset)
    || !strcmp("--generator-sine", *argv_offset))
  {
    rtn_generator_paramset =
      new genSinePs<double>(x_shift, x_scale, y_shift, y_scale,
        samps_per);
  }
  else if
     ( !strcmp("-gsquare", *argv_offset)
    || !strcmp("--generator-square", *argv_offset))
  {
    rtn_generator_paramset =
      new genSquarePs<double>(x_shift, x_scale, y_shift, y_scale,
        samps_per, samps_per / 2);
  }
  else
  {
    return nullptr;
  }

  // ret.
  return rtn_generator_paramset;
}

outPs* outPs_from_cli(char** argv_offset)
{
  // vars.
  int32_t uid_out = 0;
  outPs* rtn_out_pipe_paramset;

  // marshal in the 'out' UID.
  //
  bool parse_uid_ok = midv_parse_int( *(argv_offset + 1), uid_out);
  if (!parse_uid_ok)
  {
    // second arg to 'OUTPUT-PIPE' is bad.
    return nullptr;
  }

  // construct the corresponding 'outPs',
  //   or exit (invalid switch handed in).
  //
  if ( !strcmp("-opr", *argv_offset)
    || !strcmp("--output-pipe-ram", *argv_offset))
  {
    if (db_ringbuffers.find(uid_out) == db_ringbuffers.end())
      { db_ringbuffers[uid_out] = make_RingBuffer(); }
    rtn_out_pipe_paramset = new outRamPs(db_ringbuffers[uid_out]);
  }
  else if
     ( !strcmp("-opf", *argv_offset)
    || !strcmp("--output-pipe-file", *argv_offset))
  {
    std::stringstream ss;
    ss << "nodebench-file" << uid_out << ".dat";
    rtn_out_pipe_paramset = new outFilePs(ss.str());

    std::ofstream merely_open(ss.str(), std::ios_base::trunc);
    merely_open.close();
  }
  else 
  {
    // first arg to 'OUTPUT-PIPE' is bad.
    return nullptr;
  }

  // ret.
  return rtn_out_pipe_paramset;
}

inPs* inPs_from_cli(char** argv_offset)
{
  // vars.
  int32_t uid_in = 0;
  inPs* rtn_in_pipe_paramset;

  // marshal in the 'in' UID.
  //
  bool parse_uid_ok = midv_parse_int( *(argv_offset + 1), uid_in);
  if (!parse_uid_ok)
  {
    // second arg to 'INPUT-PIPE' is bad.
    return nullptr;
  }

  // construct the corresponding 'inPs', 
  //   or exit (invalid switch handed in).
  //
  if ( !strcmp("-ipr", *argv_offset)
    || !strcmp("--input-pipe-ram", *argv_offset))
  {
    if (db_ringbuffers.find(uid_in) == db_ringbuffers.end())
      { db_ringbuffers[uid_in] = make_RingBuffer(); }
    rtn_in_pipe_paramset = new inRamPs(db_ringbuffers[uid_in]);
  }
  else if
     ( !strcmp("-ipf", *argv_offset)
    || !strcmp("--input-pipe-file", *argv_offset))
  {
    std::stringstream ss;
    ss << "nodebench-file" << uid_in << ".dat";
    rtn_in_pipe_paramset = new inFilePs(ss.str());

    std::ifstream check_exists(ss.str());
    if (check_exists.good() == false)
    {
      std::ofstream merely_open(ss.str(), std::ios_base::trunc);
      merely_open.close();
    }
  }
  else
  {
    // first arg to 'INPUT-PIPE' is bad.
    return nullptr;
  }

  // ret.
  return rtn_in_pipe_paramset;
}

int main(int argc, char** argv)
{
  // print usage.
  if (argc == 1) // `nodebench`
  {
    printUsage();
    return 0;
  }

  // vars.
  std::vector<IStorableNode*> all_nodes;
  std::vector<nodePs*>        all_nodePs;

  // iterate through cli args.
  //   advancement of 'n_argv' is handled in cases.
  //
  for (int32_t n_argv = 1; n_argv < argc;)
  {
    char* it_argv = argv[n_argv];

    if (strcmp(it_argv, "byte-node") == 0)
    {
      std::cout << "nodebench: constructing byte-node..." << std::endl;
      if (n_argv + (NUM_BYTENODE_CLI_ARGS - 1) >= argc)
      {
        gl_error_main = -1;
        printBadArgs();
        goto label_cleanup;
      }

      inPs* in_pipe_paramset = inPs_from_cli( &argv[n_argv + 1] );
      outPs* out_pipe_paramset = outPs_from_cli( &argv[n_argv + 3] );
      if (in_pipe_paramset == nullptr || out_pipe_paramset == nullptr)
      {
        gl_error_main = -1;
        printBadArgs();
        goto label_cleanup;
      }

      all_nodePs.push_back(new byteNodePs<double>(in_pipe_paramset, out_pipe_paramset));

      // advance the 'argv' indexer.
      n_argv += NUM_BYTENODE_CLI_ARGS;
    }
    else if (strcmp(it_argv, "source-node") == 0)
    {
      std::cout << "nodebench: constructing source-node..." << std::endl;
      if (n_argv + (NUM_SOURCENODE_CLI_ARGS - 1) >= argc)
      {
        gl_error_main = -1;
        printBadArgs();
        goto label_cleanup;
      }

      genPs<double>* generator_paramset = genPs_from_cli( &argv[n_argv + 1] );
      outPs* out_pipe_paramset = outPs_from_cli( &argv[n_argv + 7] );
      if (generator_paramset == nullptr || out_pipe_paramset == nullptr)
      {
        gl_error_main = -1;
        printBadArgs();
        goto label_cleanup;
      }

      all_nodePs.push_back(new sourceNodePs<double>(generator_paramset, out_pipe_paramset));

      // advance the 'argv' indexer.
      n_argv += NUM_SOURCENODE_CLI_ARGS;
    }
    else if (strcmp(it_argv, "show-node") == 0)
    {
      std::cout << "nodebench: constructing show-node..." << std::endl;
      if (n_argv + (NUM_SHOWNODE_CLI_ARGS - 1) >= argc)
      {
        gl_error_main = -1;
        printBadArgs();
        goto label_cleanup;
      }

      inPs* in_pipe_paramset = inPs_from_cli( &argv[n_argv + 1] );
      dispPs<double>* display_paramset = dispPs_from_cli( &argv[n_argv + 3] );
      if (in_pipe_paramset == nullptr || display_paramset == nullptr)
      {
        gl_error_main = -1;
        printBadArgs();
        goto label_cleanup;
      }

      all_nodePs.push_back(new showNodePs<double>(in_pipe_paramset, display_paramset));

      // advance the 'argv' indexer.
      n_argv += NUM_SHOWNODE_CLI_ARGS;
    }
    else if (strcmp(it_argv, "core-node") == 0)
    {
      std::cout << "nodebench: constructing core-node..." << std::endl;
      if (n_argv + (NUM_CORENODE_CLI_ARGS - 1) >= argc)
      {
        gl_error_main = -1;
        printBadArgs();
        goto label_cleanup;
      }

      inPs* in_pipe_paramset = inPs_from_cli( &argv[n_argv + 1]);
      procPs<double, double>* processor_paramset = procPs_from_cli( &argv[n_argv + 3] );
      outPs* out_pipe_paramset = outPs_from_cli( &argv[n_argv + 5] );
      if (in_pipe_paramset == nullptr || processor_paramset == nullptr || out_pipe_paramset == nullptr)
      {
        gl_error_main = -1;
        printBadArgs();
        goto label_cleanup;
      }

      all_nodePs.push_back(new coreNodePs<double, double>(
        in_pipe_paramset, processor_paramset, out_pipe_paramset));

      // advance the 'argv' indexer.
      n_argv += NUM_CORENODE_CLI_ARGS;
    }
    else if (strcmp(it_argv, "mixer-node") == 0)
    {
      std::cout << "nodebench: constructing mixer-node..." << std::endl;
      if (n_argv + (NUM_MIXERNODE_CLI_ARGS - 1) >= argc)
      {
        gl_error_main = -1;
        printBadArgs();
        goto label_cleanup;
      }

      inPs* in_pipe1_paramset = inPs_from_cli( &argv[n_argv + 1] );
      inPs* in_pipe2_paramset = inPs_from_cli( &argv[n_argv + 3] );
      outPs* out_pipe_paramset = outPs_from_cli( &argv[n_argv + 5] );
      if (in_pipe1_paramset == nullptr || in_pipe2_paramset == nullptr || out_pipe_paramset == nullptr)
      {
        gl_error_main = -1;
        printBadArgs();
        goto label_cleanup;
      }

      all_nodePs.push_back(new mixerNodePs<double, double>(
        in_pipe1_paramset, in_pipe2_paramset, out_pipe_paramset));

      // advance the 'argv' indexer.
      n_argv += NUM_MIXERNODE_CLI_ARGS;
    }
    else
    {
      gl_error_main = -1;
      printBadArgs();
      goto label_cleanup;
    }
  }

  // run the nodes.
  // 
  std::cout << "nodebench: starting nodes..." << std::endl;

  for (auto each_nodePs : all_nodePs)
  {
    all_nodes.push_back(each_nodePs->Make());
  }

  std::cout << "nodebench: nodes started." << std::endl;

  std::cout << "nodebench: waiting for nodes to run..." << std::endl;

  std::this_thread::sleep_for(std::chrono::milliseconds(10000));

  std::cout << "nodebench: nodes done running" << std::endl;

  label_cleanup:

    std::cout << "nodebench: SKIPPING closing ringbuffers..." << std::endl;
    // for (auto each : db_ringbuffers)
    // { each.second->Close();
    // }

    std::cout << "nodebench: deleting 'Node's..." << std::endl;
    for (auto each : all_nodes)
      { delete each; }

    std::cout << "nodebench: deleting 'nodePs's..." << std::endl;
    for (auto each : all_nodePs)
      { delete each; }

    std::cout << "nodebench: deleting 'RingBuffer's..." << std::endl;
    for (auto each : db_ringbuffers)
      { delete each.second; } // std::pair< int32_t, RingBuffer<char>* >

    if (gl_error_main == 0)
    {
      std::cout << "nodebench: exit ok" << std::endl;
    }
    else
    {
      std::cout << "nodebench: exit with error" << std::endl;
    }

  return gl_error_main;
}
