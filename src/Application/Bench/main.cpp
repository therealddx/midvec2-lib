// bench 
// 
// Testbench code for exercising nontrivial functionalities
// of this library.
// 
// Reference `printUsage` for present scope of this test application.
//

#include "stdinclude.hpp"
#include "bench.hpp"
#include "BenchLog.hpp"
#include "TestInputPipeFile.hpp"
#include "TestInputPipeUdp.hpp"
#include "TestInputPipeRam.hpp"

extern int32_t            gl_error_main;
extern uint32_t           gl_sequential_test_id;
extern std::atomic<bool>* gl_rb_master_cancellation_token;
extern BenchLog*          gl_bench_log;

int main(int argc, const char** argv)
{
  if (argc <= 1)
  {
    // Notify + ret.
    printUsage();
    return 0;
  }

  std::cout << "bench: entry..." << std::endl;

  // vars-- global.
  //
  gl_rb_master_cancellation_token = new std::atomic<bool>(false);
  gl_bench_log = new BenchLog(std::cout);

  // vars-- test-specific items.
  //
  // These std::vectors are associated lists.
  // Any given test is linked by the same index 'n_assoc' across
  // each set of these collections.
  // 
  std::vector<InputPipeFileArgs> v_InputPipeFileArgs; // Collection for ipf args.
  std::vector<inFilePs*> v_inFilePs;                  // Paramsets for InputPipeFile's.
  std::vector<InputPipeFile*> v_InputPipeFile;        // Collection of tested objects.

  std::vector<InputPipeUdpArgs> v_InputPipeUdpArgs; // Collection for ipu args.
  std::vector<inUdpPs*> v_inUdpPs;                  // Paramsets for InputPipeUdp's.
  std::vector<InputPipeUdp*> v_InputPipeUdp;        // Collection of tested objects.

  std::vector<InputPipeRamArgs> v_InputPipeRamArgs; // Collection for ipr args.
  std::vector<inRamPs*> v_inRamPs;                  // Paramsets for InputPipeRam's.
  std::vector<InputPipeRam*> v_InputPipeRam;        // Collection of tested objects.
  std::vector<RingBuffer<char>*> v_ramRingBuffers;  // Collection of RingBuffer<char>'s used in the app.

  gl_bench_log->log("bench: scanning CLI args...\n");

  // Read the CLI args.
  for (int32_t n_argv = 1; n_argv < argc;)
  {
    if ( strcmp(argv[n_argv], "--input-pipe-file") == 0
      || strcmp(argv[n_argv], "-ipf") == 0)
    {
      gl_bench_log->log("bench: found \"--input-pipe-file\"...\n");

      // Disregard if insufficient CLI args.
      // 
      if (((n_argv + NUM_IPF_CLI_ARGS - 1) < argc) == false)
        { printErrorBadArgv(); goto label_cleanup_exit; }
     
      // Marshal the '-ipf' CLI args.
      InputPipeFileArgs to_add;
      ErrorCode error_marshal_ipf = marshalInputPipeFileArgs(&argv[n_argv], to_add);

      if (error_marshal_ipf != ErrorCode::Ok)
        { printErrorBadArgv(); goto label_cleanup_exit; }

      // Report the '-ipf' CLI args.
      {
        std::stringstream ss_msg;
        
        ss_msg << "bench: creating a test file:" << std::endl 
          << "  '" << to_add.num_msg << "'" << " messages," << std::endl
          << "    each of type '" << to_add.t_back_storage << "'," 
            << " and backing data size '" << to_add.t_back_size << "' bits"
          << std::endl;
        
        gl_bench_log->log(ss_msg.str());
      }

      // Store the CLI args for later.
      v_InputPipeFileArgs.push_back(to_add);

      // Skip ahead by #used CLI args.
      n_argv += NUM_IPF_CLI_ARGS;
    }
    else if ( strcmp(argv[n_argv], "--input-pipe-udp") == 0
           || strcmp(argv[n_argv], "-ipu") == 0)
    {
      gl_bench_log->log("bench: found \"--input-pipe-udp\"...\n");

      // Disregard if insufficient CLI args.
      // 
      if (((n_argv + NUM_IPU_CLI_ARGS - 1) < argc) == false)
        { printErrorBadArgv(); goto label_cleanup_exit; }
     
      // Marshal the '-ipu' CLI args.
      InputPipeUdpArgs to_add;
      ErrorCode error_marshal_ipu = marshalInputPipeUdpArgs(&(argv[n_argv]), to_add);

      if (error_marshal_ipu != ErrorCode::Ok)
        { printErrorBadArgv(); goto label_cleanup_exit; }

      // Report the '-ipu' CLI args.
      {
        std::stringstream ss_msg;

        ss_msg << "bench: creating a UDP test sender:" << std::endl
          << "  '" << to_add.num_msg << "' messages," << std::endl
          << "    each of type '" << to_add.t_back_storage << "',"
            << " and backing data size '" << to_add.t_back_size << "' bits" << std::endl
          << "  sending data to '" << to_add.ipv4 << ":" << to_add.port << "', " << std::endl
          << "  and sleeping '" << to_add.msg_sleep << "' useconds per sent message." << std::endl;

        gl_bench_log->log(ss_msg.str());
      }

      // Store the CLI args for later.
      v_InputPipeUdpArgs.push_back(to_add);

      // Skip ahead by #used CLI args.
      n_argv += NUM_IPU_CLI_ARGS;
    }
    else if ( strcmp(argv[n_argv], "--input-pipe-ram") == 0
           || strcmp(argv[n_argv], "-ipr") == 0)
    {
      gl_bench_log->log("bench: found \"--input-pipe-ram\"...\n");

      // Disregard if insufficient CLI args.
      // 
      if (((n_argv + NUM_IPR_CLI_ARGS - 1) < argc) == false)
        { printErrorBadArgv(); goto label_cleanup_exit; }

      // Marshal the '-ipr' CLI args.
      InputPipeRamArgs to_add;
      ErrorCode error_marshal_ipr = marshalInputPipeRamArgs(&(argv[n_argv]), to_add);

      if (error_marshal_ipr != ErrorCode::Ok)
        { printErrorBadArgv(); goto label_cleanup_exit; }

      // Report the '-ipr' CLI args.
      {
        std::stringstream ss_msg;

        ss_msg << "bench: creating a RAM test buffer: " << std::endl
          << "  '" << to_add.num_msg << "' messages," << std::endl
          << "    each of type '" << to_add.t_back_storage << "',"
            << " and backing data size '" << to_add.t_back_size << "' bits" << std::endl;

        gl_bench_log->log(ss_msg.str());
      }

      // Store the CLI args for later.
      v_InputPipeRamArgs.push_back(to_add);

      // Skip ahead by #used CLI args.
      n_argv += NUM_IPR_CLI_ARGS;
    }
    else
      { printErrorBadArgv(); goto label_cleanup_exit; }
  }

  // Don't continue if there's nothing to create.
  if ( v_InputPipeFileArgs.size() == 0
    && v_InputPipeUdpArgs.size() == 0
    && v_InputPipeRamArgs.size() == 0 )
  {
    gl_bench_log->log("bench: no InputPipe tests created, exiting...\n");
    return 0;
  }

  // Run each requested InputPipeFile test.
  // For each InputPipeFileArgs:
  // 
  for (uint32_t n_assoc = 0; n_assoc < v_InputPipeFileArgs.size(); n_assoc++)
  {
    // Make the test file.
    ErrorCode error_makeTestFile = switch_makeTestFile(v_inFilePs, v_InputPipeFileArgs[n_assoc]);

    if (error_makeTestFile != ErrorCode::Ok)
      { printErrorBadArgv(); goto label_cleanup_exit; }

    // Make the InputPipeFile.
    v_InputPipeFile.push_back(dynamic_cast<InputPipeFile*>(v_inFilePs[n_assoc]->Make()));

    gl_bench_log->log("bench: testing InputPipeFile...\n");

    // Test the InputPipeFile.
    switch_TestInputPipeFile(v_InputPipeFile[n_assoc], v_InputPipeFileArgs[n_assoc]);

    // Increment the 'test id' variable.
    gl_sequential_test_id++;
  }

  // Run each requested InputPipeUdp test.
  // For each InputPipeUdpArgs:
  // 
  for (uint32_t n_assoc = 0; n_assoc < v_InputPipeUdpArgs.size(); n_assoc++)
  {
    // Make and store a inUdpPs.
    v_inUdpPs.push_back(new inUdpPs(v_InputPipeUdpArgs[n_assoc].ipv4, v_InputPipeUdpArgs[n_assoc].port));

    // Make and store a InputPipeUdp.
    v_InputPipeUdp.push_back(dynamic_cast<InputPipeUdp*>(v_inUdpPs[n_assoc]->Make()));

    // Start the worker for InputPipeUdp's listening.
    std::thread worker_receive(
      &switch_TestInputPipeUdp, v_InputPipeUdp[n_assoc], v_InputPipeUdpArgs[n_assoc]);

    std::this_thread::sleep_for(std::chrono::seconds(3));

    // Start the worker for sending the test data.
    std::thread worker_send(
      &switch_sendTestData, v_InputPipeUdpArgs[n_assoc]);

    // Wait for both workers to finish.
    worker_receive.join();
    worker_send.join();

    // Increment the 'test id' variable.
    gl_sequential_test_id++;
  }

  // Run each requested InputPipeRam test.
  // For each InputPipeRamArgs:
  // 
  for (uint32_t n_assoc = 0; n_assoc < v_InputPipeRamArgs.size(); n_assoc++)
  {
    // Make and store a 'RingBuffer<char>'.
    v_ramRingBuffers.push_back(
      new RingBuffer<char>(v_InputPipeRamArgs[n_assoc].rb_size));

    // Make and store a inRamPs.
    v_inRamPs.push_back(new inRamPs(v_ramRingBuffers[n_assoc], gl_rb_master_cancellation_token));

    // Make and store a InputPipeRam.
    v_InputPipeRam.push_back(dynamic_cast<InputPipeRam*>(v_inRamPs[n_assoc]->Make()));

    // Start the worker thread for writing the test data.
    std::thread worker_send(
      &switch_writeRingBuffer, v_InputPipeRam[n_assoc]->GetRingBuffer(), v_InputPipeRamArgs[n_assoc]);

    // Start the worker thread for InputPipeRam's listening.
    std::thread worker_receive(
      &switch_TestInputPipeRam, v_InputPipeRam[n_assoc], v_InputPipeRamArgs[n_assoc]);

    // The test is started when...
    //   the write worker has made its first `RingBuffer<T>::Write` call.
    // 
    gl_bench_log->log("bench: waiting for first write to ringbuffer...\n");
    {
      while (true) // note: high-rate polling still might not capture entry for a low-volume test.
      {
        if (v_ramRingBuffers[n_assoc]->GetOccupancy() > 0) { break; }
        std::this_thread::sleep_for(std::chrono::milliseconds(1));
      }
    }
    gl_bench_log->log("bench: first write detected\n");

    // The test is done when...
    //   occupancy has stayed constant long enough (ideally, '0' long enough).
    // 
    gl_bench_log->log("bench: waiting for ringbuffer to be emptied...\n");
    {
      int32_t prev_occupancy = 0;
      int32_t cur_occupancy = 0;
      int32_t n_checks_constant_occupancy = 0;

      while (true) // occupancy polling-- 500ms x 10 polls == 2s
      {
        prev_occupancy = cur_occupancy;
        cur_occupancy = v_ramRingBuffers[n_assoc]->GetOccupancy();

        if (prev_occupancy == cur_occupancy) { n_checks_constant_occupancy++; }
        else { n_checks_constant_occupancy = 0; }

        std::stringstream ss_msg;
        ss_msg << "bench: monitoring InputPipeRam test: occupancy '"
          << cur_occupancy << "'" << std::endl;
        gl_bench_log->log(ss_msg.str());

        if (n_checks_constant_occupancy == 10) { break; }

        std::this_thread::sleep_for(std::chrono::milliseconds(500));
      }
    }
    gl_bench_log->log("bench: ringbuffer emptied\n");

    // Unleash the write and read workers.
    //
    gl_rb_master_cancellation_token->store(true); // bails out any `RingBuffer<T>::Read|Write`.

    // Both threads should die cleanly.
    //
    gl_bench_log->log("bench: ram test, joining sender...\n");
    worker_send.join();
    gl_bench_log->log("bench: ram test, sender joined\n");

    gl_bench_log->log("bench: ram test, joining receiver...\n");
    worker_receive.join();
    gl_bench_log->log("bench: ram test, receiver joined\n");

    // Increment the 'test id' variable.
    gl_sequential_test_id++;
  }

  label_cleanup_exit:

    // Delete each InputPipeFile.
    for (InputPipeFile* each_InputPipeFile : v_InputPipeFile)
      { delete each_InputPipeFile; }

    // Delete each inFilePs.
    for (inFilePs* each_inFilePs : v_inFilePs)
      { delete each_inFilePs; }

    // Delete each InputPipeUdp.
    for (InputPipeUdp* each_InputPipeUdp : v_InputPipeUdp)
      { delete each_InputPipeUdp; }
    
    // Delete each inUdpPs.
    for (inUdpPs* each_inUdpPs : v_inUdpPs)
      { delete each_inUdpPs; }

    // Delete each InputPipeRam.
    for (InputPipeRam* each : v_InputPipeRam)
      { delete each; }

    // Delete each inRamPs.
    for (inRamPs* each_inRamPs : v_inRamPs)
      { delete each_inRamPs; }

    // Delete each RingBuffer.
    for (auto each : v_ramRingBuffers)
      { delete each; }

    // Delete each extern that needs it.
    delete gl_rb_master_cancellation_token;
    delete gl_bench_log;

    // ret.
    if (gl_error_main == 0)
    {
      std::cout << "bench: exit OK" << std::endl;
    }
    else
    {
      std::cout << "bench: exiting with error. (" << gl_error_main << ")" << std::endl;
    }
    return gl_error_main;
}

