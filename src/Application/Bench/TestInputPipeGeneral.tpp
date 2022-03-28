#ifndef TESTINPUTPIPEGENERAL_TPP
#define TESTINPUTPIPEGENERAL_TPP

template <class T_d>
void echoTestFile
  ( const std::vector<uint8_t>& arg_message
  , uint32_t arg_n_message
  , std::ostream& arg_ostream
  )
{
  // Start of printout.
  arg_ostream << "Message: " << std::dec << arg_n_message << std::endl;

  // Print hex format.
  arg_ostream << "... { ";
  for (uint8_t each_byte : arg_message)
  {
    arg_ostream << "0x" << std::hex << static_cast<uint32_t>(each_byte) << " ";
  } arg_ostream << "}" << std::endl;

  // Print base-10 format.
  arg_ostream << "... { ";
  for (uint8_t each_byte : arg_message)
  {
    arg_ostream << std::dec << static_cast<uint32_t>(each_byte) << " ";
  } arg_ostream << "}" << std::endl;

  // Print 'MIDV' + 'T_d' as its own default string representation.
  {
    // vars.
    uint32_t n_byte = 0;
    T_d msg_backing_value = 0;
    uint8_t* p_msg_backing_value = reinterpret_cast<uint8_t*>(&msg_backing_value);

    arg_ostream << "... { ";

    for (n_byte
      ; n_byte < sizeof(MessageConstants::MESSAGE_HEADER)
      ; n_byte++)
    {
      arg_ostream << arg_message[n_byte] << " ";
    }

    for (n_byte
      ; n_byte < sizeof(MessageConstants::MESSAGE_HEADER) + sizeof(T_d)
      ; n_byte++)
    {
      if (MessageConstants::IS_LITTLE_ENDIAN == false)
      {
        // Big-endian: Bytes appear in order.
        *p_msg_backing_value++ = arg_message[n_byte];
      }
      else
      {
        // Little-endian: Bytes appear in reverse-order.
        *p_msg_backing_value++ =
          arg_message
          [ sizeof(MessageConstants::MESSAGE_HEADER) + sizeof(T_d) - 1
          - (n_byte - sizeof(MessageConstants::MESSAGE_HEADER))
          ];
      }
    }

    arg_ostream << std::dec << msg_backing_value << " }" << std::endl;
  }
}

#endif // TESTINPUTPIPEGENERAL_TPP

