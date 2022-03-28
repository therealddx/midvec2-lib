#ifndef TESTINPUTPIPEGENERAL_HPP
#define TESTINPUTPIPEGENERAL_HPP

#include "stdinclude.hpp"

// echoTestFile
//   Print the contents of message 'const std::vector<uint8_t>&',
//     (the 'uint32_t'th message to have been read by the InputPipeFile),
//   to 'std::ostream&', with a common formatting convention.
// 
//   The backing data type of the messages is given by type parameter 'T_d'.
// 
template <class T_d>
void echoTestFile(const std::vector<uint8_t>&, uint32_t, std::ostream&);

#include "TestInputPipeGeneral.tpp"

#endif // TESTINPUTPIPEGENERAL_HPP

