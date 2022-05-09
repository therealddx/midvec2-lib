/**
 * reference LICENSE file provided.
 *
 * @file DisplayFile.hpp
 * Implementation of DisplayBase to populate a human-readable textfile.
 *
 */

#ifndef DISPLAYFILE_HPP
#define DISPLAYFILE_HPP

#include <iostream>
#include <string>
#include <fstream>
#include "DisplayBase.hpp"

/**
 * @class DisplayFile
 */
template <class T_in>
class DisplayFile : public DisplayBase<T_in>
{
public:

 /**
  * DisplayFile
  *
  * @param[in] arg_fqFile
  * Fully-qualified path to file that will hold display data.
  */	
  DisplayFile(std::string arg_fqFile);

  /**
   * ~DisplayFile
   * Closes the handle to the display text file.
   */
  ~DisplayFile();

  /**
   * Update
   * Satisfies base class.
   */
  void Update(T_in arg_newValue);

private:

  uint32_t _sampleCount;
  std::string _fqFile;
  std::ofstream _outputFile;

};

#endif // DISPLAYFILE_HPP

