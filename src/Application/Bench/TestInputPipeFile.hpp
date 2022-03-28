#ifndef TESTINPUTPIPEFILE_HPP
#define TESTINPUTPIPEFILE_HPP

#include "stdinclude.hpp"
#include "TestInputPipeGeneral.hpp"

// makeTestFile
//   Fill the file at 'std::string' with 'uint32_t' MIDV messages, each with 
//   backing type defined by 'T_d'.
// 
//   If 'bool' is true, use `echoTestFile` to echo the MIDV messages to
//   a separate file, representing expected message content of the file.
// 
template <class T_d>
ErrorCode makeTestFile(std::string, uint32_t, bool);

// TestInputPipeFile
//   Given an InputPipeFile, exercise its interface functionality.
// 
//   Use templated type 'T_d' to determine the t-ype of d-ata
//     being extracted from the file.
// 
template <class T_d>
void TestInputPipeFile(InputPipeFile*);

// deleteFile
//   Delete the file at 'arg_file_path'.
//   If deletion succeeds, report 'ErrorCode::Ok'.
// 
ErrorCode deleteFile(std::string);

#include "TestInputPipeFile.tpp"

#endif // TESTINPUTPIPEFILE_HPP

