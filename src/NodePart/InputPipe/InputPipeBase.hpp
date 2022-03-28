/* 
 * reference LICENSE file provided.
 *
 * InputPipeBase.hpp.
 * Defines a base class for reading bytes from hardware into a 
 * ready-for-wire Message instance.
 *
 */

#ifndef INPUTPIPEBASE_HPP
#define INPUTPIPEBASE_HPP

#include <stdint.h>
#include <sys/types.h>

class InputPipeBase
{
public:

  // 
  // Ctor / Dtor.
  // Blank in base class.
  //
  InputPipeBase() { };
  virtual ~InputPipeBase() { };

  // 
  // GetMessage.
  // Seek forward into the bytestream of this HW IF.
  // Read those bytes into one serialized Message<T>.
  //
  virtual char* GetMessage(size_t arg_backerLength) = 0;

private:

};

#endif // INPUTPIPEBASE_HPP

