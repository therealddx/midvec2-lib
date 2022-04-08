/*
 * reference LICENSE file provided.
 *
 * DisplayFile.hpp.
 * Implements DisplayBase for putting numerical data into a human-readable
 * text file.
 *
 */

#ifndef DISPLAYFILE_HPP
#define DISPLAYFILE_HPP

#include <iostream>
#include <string>
#include <fstream>
#include "DisplayBase.hpp"

template <class T_in>
class DisplayFile : public DisplayBase<T_in>
{
public:
 
  // 
  // Ctor.
  //
  DisplayFile(std::string arg_fqFile);

  // 
  // Dtor.
  //
  ~DisplayFile();

  // 
  // Update.
  //
  void Update(T_in arg_newValue);

private:

  uint32_t _sampleCount;
  std::string _fqFile;
  std::ofstream _outputFile;

};

#endif // DISPLAYFILE_HPP

