/*
 * reference LICENSE file provided.
 *
 * DisplayBase.hpp.
 * Presents abstract class for displaying input data. Given any new input
 * value, adds that new value to the display. Data is assumed to be of 
 * two-dimensional format, e.g. y = f(x).
 *
 */

#ifndef DISPLAYBASE_HPP
#define DISPLAYBASE_HPP

template <class T_in>
class DisplayBase
{
public:

  // 
  // Ctor.
  //
  DisplayBase() { } ;

  // 
  // Dtor.
  //
  virtual ~DisplayBase() { } ;

  // 
  // Update.
  // Hand-off from master class.
  //
  virtual void UpdateMarshal(char* arg_data);

  // 
  // Update.
  // Add a new value to update the display.
  //
  virtual void Update(T_in arg_newValue) = 0;

};

#endif // DISPLAYBASE_HPP

