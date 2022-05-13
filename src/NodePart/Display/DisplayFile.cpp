/**
 * reference LICENSE file provided.
 *
 * @file DisplayFile.cpp
 * Implements DisplayFile.hpp
 *
 */

#include <Types/Complex.hpp>
#include "DisplayFile.hpp"

template <class T_in>
DisplayFile<T_in>::DisplayFile(std::string arg_fqFile)
: _fqFile(arg_fqFile)
{
  _sampleCount = 0;

  // open file.
  _outputFile.open(_fqFile, std::ofstream::out | std::ofstream::app);
  _outputFile << "midvec2, DisplayFile, " << _fqFile << std::endl;
}

template <class T_in>
DisplayFile<T_in>::~DisplayFile()
{
  // close file.
  _outputFile.close();
}

template <class T_in>
void DisplayFile<T_in>::Update(T_in arg_newValue)
{
  // append to file.
  _outputFile << _sampleCount++ << ":" << arg_newValue << std::endl;

  // overflow notification.
  if (_sampleCount == 0)
  {
    _outputFile << "# sample count overflow; resetting count to 0"
    << std::endl;
  }
}

template class DisplayFile<double>;
template class DisplayFile<Complex<double>>;

