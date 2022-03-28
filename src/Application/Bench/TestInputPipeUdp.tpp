#ifndef TESTINPUTPIPEUDP_TPP
#define TESTINPUTPIPEUDP_TPP

#include "BenchLog.hpp"

extern uint32_t  gl_sequential_test_id;
extern BenchLog* gl_bench_log;

template<class T_d>
ErrorCode sendTestData(uint32_t arg_num_msg, std::string arg_ipv4, uint16_t arg_port, uint32_t arg_usleep)
{
  // vars.
  ErrorCode rtn_error = ErrorCode::Ok; // error result for entirety of method.

  // 
  // setup the outgoing data, and record it (echo it) to a file.
  // 
  std::stringstream echo_ostream_name;
  echo_ostream_name << "echo-TestInputPipeUdp-"
    << std::dec << std::setfill('0') << std::setw(4) << gl_sequential_test_id
    << ".dat";

  std::ofstream echo_ostream;
  echo_ostream.open(echo_ostream_name.str(), std::ios_base::trunc | std::ios_base::binary);

  uint32_t total_payload_size = arg_num_msg * (sizeof(MessageConstants::MESSAGE_HEADER) + sizeof(T_d));
  uint8_t* p_total_payload = static_cast<uint8_t*>(malloc(total_payload_size));
  uint8_t* it_total_payload = p_total_payload;

  // for each message:
  //   note the header.
  //   note the random backing data.
  //   echo the message to a file for later evaluation.
  // 
  for (uint32_t n_msg = 0; n_msg < arg_num_msg; n_msg++)
  {
    std::vector<uint8_t> new_message;

    for (auto b : std::string("MIDV"))
    {
      new_message.push_back(b);
      *it_total_payload++ = b;
    }

    for (uint32_t n_byte = 0; n_byte < sizeof(T_d); n_byte++)
    {
      uint8_t b = rand() & 0xff;
      new_message.push_back(b);
      *it_total_payload++ = b;
    }

    echoTestFile<T_d>(new_message, n_msg, echo_ostream);
  }

  // done setting up outgoing data:
  //   close the echo file.
  //   reset the payload byte pointer.
  // 
  echo_ostream.close();
  it_total_payload = p_total_payload;

  // 
  // setup the outgoing socket.
  // 
  struct sockaddr_in sending_socket;
  int32_t socket_fd = 0;

  sending_socket.sin_family = AF_INET;
  sending_socket.sin_port = htons(arg_port);
  inet_aton(arg_ipv4.c_str(), &sending_socket.sin_addr);
  socket_fd = socket(AF_INET, SOCK_DGRAM, 0);

  // 
  // send out the test messages.
  // 
  if (arg_usleep == 0)
  {
    while (it_total_payload != p_total_payload + total_payload_size)
    {
      // determine #bytes to ship out.
      // 
      // #bytes that are left remaining to ship out (at this point in the loop) is:
      // total_payload_size - (index in payload byte array)
      //   e.g., if (index in payload byte array) == 0, you need to ship out 'total_payload_size'.
      // 
      // and,
      // (index in payload byte array) == it_total_payload - p_total_payload
      //   e.g., if it_total_payload == p_total_payload, (index in payload byte array) == 0.
      // 
      // so, 
      // #bytes that are left remaining to ship out is:
      // total_payload_size - (it_total_payload - p_total_payload)
      // total_payload_size - it_total_payload + p_total_payload
      // 
      int32_t num_bytes_packaged
        = p_total_payload + total_payload_size - it_total_payload >= MAX_BYTES_UDP_DATAGRAM
        ? MAX_BYTES_UDP_DATAGRAM
        : p_total_payload + total_payload_size - it_total_payload;

      // run the 'sendto'.
      int32_t num_bytes_sent = sendto
        ( socket_fd
        , it_total_payload
        , num_bytes_packaged
        , 0
        , reinterpret_cast<struct sockaddr*>(&sending_socket)
        , sizeof(sending_socket)
        );
      
      // #bytes packaged must equal #bytes sent.
      if (num_bytes_sent != num_bytes_packaged)
      {
        {
          std::stringstream ss_msg;

          ss_msg << "sendTestData: bad udp sendto:"        << std::endl
            << "  num_bytes_sent: " << num_bytes_sent         << std::endl
            << "  num_bytes_packaged: " << num_bytes_packaged << std::endl;

          gl_bench_log->log(ss_msg.str());
        }

        rtn_error = ErrorCode::Shrug;
        goto label_cleanup_exit;
      }

      // increment through.
      it_total_payload += num_bytes_packaged;
    }
  }
  else
  {
    // not supported yet.
    {
      std::stringstream ss_msg;
      ss_msg << "sendTestData: usleep not yet supported" << std::endl;
      gl_bench_log->log(ss_msg.str());
    }
    rtn_error = ErrorCode::Shrug;
    goto label_cleanup_exit;
  }

  label_cleanup_exit:

    // free the malloc.
    free(p_total_payload);
  
    // close the socket.
    close(socket_fd);

    // report.
    {
      std::stringstream ss_msg;

      ss_msg << "bench: `sendTestData<T>` complete. send-data logged to "
        << echo_ostream_name.str() << std::endl;

      gl_bench_log->log(ss_msg.str());
    }

    // ret.
    return rtn_error;
}

template <class T_d>
ErrorCode TestInputPipeUdp(InputPipeUdp* arg_ipu)
{
  // vars.
  std::stringstream retr_ostream_name;
  std::ofstream retr_ostream;
  uint32_t rx_msg_count = 0;
  bool latch_rx = false;

  // setup the logging ostream.
  retr_ostream_name << "retr-TestInputPipeUdp-"
    << std::dec << std::setfill('0') << std::setw(4) << gl_sequential_test_id
    << ".dat";
  retr_ostream.open(retr_ostream_name.str());

  // for as long as there are messages to obtain:
  while (true)
  {
    // get a message.
    uint8_t* p_midv_message = reinterpret_cast<uint8_t*>(arg_ipu->GetMessage(sizeof(T_d)));

    if (p_midv_message == NULL && latch_rx == true) { break; }

    if (p_midv_message != NULL)
    {
      latch_rx = true;

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

    ss_msg << "bench: `TestInputPipeUdp<T>` complete. receive-data logged to "
      << retr_ostream_name.str() << std::endl;

    gl_bench_log->log(ss_msg.str());
  }

  // ret.
  retr_ostream.close();
  return ErrorCode::Ok;
}

#endif // TESTINPUTPIPEUDP_TPP

