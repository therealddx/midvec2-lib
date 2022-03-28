#ifndef TESTINPUTPIPERAM_TPP
#define TESTINPUTPIPERAM_TPP

#include <atomic>
#include "BenchLog.hpp"

extern uint32_t           gl_sequential_test_id;
extern std::atomic<bool>* gl_rb_master_cancellation_token;
extern BenchLog*          gl_bench_log;

template <class T_d>
ErrorCode writeRingBuffer(RingBuffer<char>* arg_ring_buffer, uint32_t arg_num_msg)
{
  // vars.
  ErrorCode rtn_error = ErrorCode::Ok;
  std::vector<std::vector<char>> all_messages;
  std::vector<char> v_payload;

  // 
  // setup the outgoing data, and record it (echo it) to a file.
  // 
  std::stringstream echo_ostream_name;
  echo_ostream_name << "echo-TestInputPipeRam-"
    << std::dec << std::setfill('0') << std::setw(4) << gl_sequential_test_id
    << ".dat";

  std::ofstream echo_ostream;
  echo_ostream.open(echo_ostream_name.str(), std::ios_base::trunc | std::ios_base::binary);

  // for each message:
  //   note the header.
  //   note the random backing data.
  //   echo the message to a file for later evaluation.
  // 
  for (uint32_t n_msg = 0; n_msg < arg_num_msg; n_msg++)
  {
    std::vector<uint8_t> new_message;
    std::vector<char> new_message_c;

    for (auto b : std::string("MIDV"))
    {
      new_message.push_back(b);
      new_message_c.push_back(static_cast<char>(b));
      v_payload.push_back(static_cast<char>(b));
    }

    for (uint32_t n_byte = 0; n_byte < sizeof(T_d); n_byte++)
    {
      uint8_t b = rand() & 0xff;
      new_message.push_back(b);
      new_message_c.push_back(static_cast<char>(b));
      v_payload.push_back(static_cast<char>(b));
    }

    echoTestFile<T_d>(new_message, n_msg, echo_ostream);
    all_messages.push_back(new_message_c);
  }

  // done setting up outgoing data:
  //   close the echo file.
  //   reset the payload byte pointer.
  // 
  echo_ostream.close();

  // report write entry.
  gl_bench_log->log("bench: `writeRingBuffer<T>`: filling ring buffer...\n");

  // 
  // write all bytes in 'p_total_payload' to the RingBuffer.
  // subsequently, we will hope that the InputPipeRam picks them up.
  // 
  for (auto each_b : v_payload)
  {
    arg_ring_buffer->Write(each_b, gl_rb_master_cancellation_token);
  }

  // report write exit.
  {
    std::stringstream ss_msg;

    ss_msg << "bench: `writeRingBuffer<T>`: complete, send-data logged to '" <<
      echo_ostream_name.str() << "'" << std::endl;

    gl_bench_log->log(ss_msg.str());
  }

  // ret.
  return ErrorCode::Ok;
}

template <class T_d>
ErrorCode TestInputPipeRam(InputPipeRam* arg_ipr)
{
  // vars.
  std::stringstream retr_ostream_name;
  std::ofstream retr_ostream;
  uint32_t rx_msg_count = 0;
  uint32_t num_null_checks = 0;
  uint32_t max_null_checks = 0xFFFFF;

  // setup the logging ostream.
  retr_ostream_name << "retr-TestInputPipeRam-"
    << std::dec << std::setfill('0') << std::setw(4) << gl_sequential_test_id
    << ".dat";
  retr_ostream.open(retr_ostream_name.str());

  // for as long as there are messages to obtain:
  while (true)
  {
    // get a message.
    uint8_t* p_midv_message = reinterpret_cast<uint8_t*>(arg_ipr->GetMessage(sizeof(T_d)));

    if (p_midv_message == NULL)
    {
      num_null_checks++;
      if (num_null_checks == max_null_checks)
      {
        break;
      }

      continue;
    }

    if (p_midv_message != NULL)
    {
      // reset num null-checks.
      num_null_checks = 0;

      // copy it out.
      std::vector<uint8_t> rx_midv_message;
      for (int32_t n_b = 0; n_b < sizeof(MessageConstants::MESSAGE_HEADER) + sizeof(T_d); n_b++)
      {
        rx_midv_message.push_back( *(p_midv_message + n_b) );
      }

      // report it.
      echoTestFile<T_d>(rx_midv_message, rx_msg_count++, retr_ostream);
    }
  }

  // report.
  {
    std::stringstream ss_msg;

    ss_msg << "bench: `TestInputPipeRam<T>`: complete, receive-data logged to "
      << retr_ostream_name.str() << std::endl;

    gl_bench_log->log(ss_msg.str());
  }

  // ret.
  retr_ostream.close();
  return ErrorCode::Ok;
}

#endif // TESTINPUTPIPERAM_TPP

