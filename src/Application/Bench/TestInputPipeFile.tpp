#ifndef TESTINPUTPIPEFILE_TPP
#define TESTINPUTPIPEFILE_TPP

#include "BenchLog.hpp"

extern BenchLog* gl_bench_log;

template <class T_d>
ErrorCode makeTestFile
  ( std::string arg_file_path
  , uint32_t arg_num_messages
  , bool arg_should_echo
  )
{
  // vars.
  ErrorCode rtn_error = ErrorCode::Ok;

  // Make new file handle to 'arg_file_path'.
  std::ofstream test_file(arg_file_path,
    std::ios_base::trunc | std::ios_base::binary);

  // Make new file handle for echo.
  std::ofstream* echo_file = nullptr;
  std::vector<uint8_t> echo_message;
  if (arg_should_echo)
  {
    echo_file = new std::ofstream(std::string("echo-") + arg_file_path,
      std::ios_base::trunc | std::ios_base::binary);
  }

  // If the file got opened up:
  if (test_file.is_open())
  {
    // Inject <arg_num_messages> messages to the test file(s).
    for (uint32_t n_msg = 0; n_msg < arg_num_messages; n_msg++)
    {
      // Print 'MIDV'.
      test_file << "MIDV";
      for (uint8_t each_midv_b : std::string("MIDV"))
        { echo_message.push_back(each_midv_b); }

      // Print backing data.
      for (uint8_t n_byte = 0; n_byte < sizeof(T_d); n_byte++)
      {
        uint8_t b = static_cast<uint8_t>(std::rand() & 0xFF);
        test_file << b;
        echo_message.push_back(b);
      }

      // Conditionally echo.
      if (echo_file != nullptr && echo_file->is_open())
        { echoTestFile<T_d>(echo_message, n_msg, *echo_file); }
      echo_message.clear();
    }

    // Close the file(s).
    test_file.close();
    if (echo_file != nullptr) { delete echo_file; }
  }
  else
  {
    rtn_error = ErrorCode::Shrug;
  }

  // ret.
  return rtn_error;
}

template <class T_d>
void TestInputPipeFile(InputPipeFile* arg_inputPipeFile)
{
  // 
  // verify InputPipeFile::GetMessage(): happy path.
  // 

  // vars.
  std::vector<std::vector<uint8_t>> rtn_messages;
  char* p_midv_message = NULL;

  // Read all messages out of the test file:
  do
  {
    // vars.
    std::vector<uint8_t> midv_message_to_add;

    // get a full message from the input stream.
    p_midv_message = arg_inputPipeFile->GetMessage(sizeof(T_d));
  
    // check exit condition. 
    if (p_midv_message == NULL) { break; }
 
    // copy the bytes from that char* into client storage.
    for ( uint32_t n_msg = 0
        ; n_msg < sizeof(MessageConstants::MESSAGE_HEADER) + sizeof(T_d)
        ; n_msg++)
    {
      midv_message_to_add.push_back(
        static_cast<uint8_t>(p_midv_message[n_msg]));
    }

    // Add the message to the listing.
    rtn_messages.push_back(midv_message_to_add);
  }
  while (true);

  // Put out a nice printout.
  {
    std::stringstream ss_msg;

    ss_msg << "TestInputPipeFile: echoing to " <<
      std::string("retr-") + arg_inputPipeFile->GetBasename() << "..." << std::endl;

    gl_bench_log->log(ss_msg.str());
  }

  std::ofstream retr_file(std::string("retr-") + arg_inputPipeFile->GetBasename(),
    std::ios_base::trunc | std::ios_base::binary);
  
  // For each message obtained:
  for (uint32_t n_msg = 0; n_msg < rtn_messages.size(); n_msg++)
  {
    // vars.
    auto& each_msg = rtn_messages[n_msg];

    // Check the message size.
    // It should strictly equal <header size> + <backing data size>.
    // 
    if (sizeof(MessageConstants::MESSAGE_HEADER) + sizeof(T_d)
       != each_msg.size())
    {
      {
        std::stringstream ss_msg;

        ss_msg << "Message " << n_msg << ": fail to print: conflicting message size: "
          << "expected size: "
            << sizeof(MessageConstants::MESSAGE_HEADER) + sizeof(T_d) << "; "
          << "obtained size: " << each_msg.size()
          << std::endl;

        gl_bench_log->log(ss_msg.str());
      }

      continue;
    }

    // Output the following:
    //   Composite string representing the message's bytes in hex
    //   Composite string representing the message's bytes in base-10
    //   Composite string representing the message's bytes as ASCII chars
    // 
    echoTestFile<T_d>(each_msg, n_msg, retr_file);
  }

  {
    std::stringstream ss_msg;

    ss_msg << "  done echoing to " <<
      std::string("retr-") + arg_inputPipeFile->GetBasename() << std::endl;

    gl_bench_log->log(ss_msg.str());
  }
  retr_file.close();
}

#endif // TESTINPUTPIPEFILE_TPP

