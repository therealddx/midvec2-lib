/*
 * reference LICENSE file provided.
 *
 * InputPipeFile.cpp.
 * Implements InputPipeFile.hpp.
 *
 */

// include: app.
#include "InputPipeFile.hpp"

InputPipeFile::InputPipeFile(std::string arg_fqFile)
: _fileBufIndex(0)
, _fileBufValid(0)
{
  // open file. 
  _inputFile.open(arg_fqFile, std::ifstream::in);

  // note the construction arg.
  _fqFile = arg_fqFile;
}

InputPipeFile::~InputPipeFile()
{
  // close file.
  if (_inputFile.is_open() == true)
    { _inputFile.close(); }
}

std::string InputPipeFile::GetBasename() const
{
  int32_t try_rfind = _fqFile.rfind('/');

  if (try_rfind >= 0 && try_rfind < _fqFile.size())
    { return _fqFile.substr(try_rfind + 1); }
  else
    { return _fqFile; }
}

ErrorCode InputPipeFile::GetByte(char* rtn_byte)
{
  // arg check.
  if (rtn_byte == 0) { return ErrorCode::NullPointer; }

  // get a byte from the file buffer.
  if (_fileBufIndex < _fileBufValid)
  {
    *rtn_byte = _fileBuf[_fileBufIndex];
    _fileBufIndex++;
    return ErrorCode::Ok;
  }
  else
  {
    // update the file buffer.
    memset(_fileBuf, 0,  MAX_SIZE_FILEBUF);
    _inputFile.read(_fileBuf, MAX_SIZE_FILEBUF);
    _fileBufIndex = 0;
    _fileBufValid = _inputFile.gcount();

    // get a byte from the file buffer.
    if (_fileBufIndex < _fileBufValid)
    {
      *rtn_byte = _fileBuf[_fileBufIndex];
      _fileBufIndex++;
      return ErrorCode::Ok;
    }
    else
    {
      *rtn_byte = 0;
      return ErrorCode::EofReached;
    }
  }
}

