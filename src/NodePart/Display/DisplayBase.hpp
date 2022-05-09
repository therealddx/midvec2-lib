/**
 * reference LICENSE file provided.
 *
 * @file DisplayBase.hpp
 *
 * Presents abstract class for displaying input data.
 *
 * Given any new input value, adds that new value to the display.
 */

#ifndef DISPLAYBASE_HPP
#define DISPLAYBASE_HPP

/**
 * @class DisplayBase
 */
template <class T_in>
class DisplayBase
{
public:

  /**
   * DisplayBase
   */
  DisplayBase() { } ;

  /**
   * ~DisplayBase
   */
  virtual ~DisplayBase() { } ;

  /**
   * UpdateMarshal
   * Marshals argument pointer into user data of type 'T_in'; and
   * Calls `Update` on that user data.
   *
   * @param[in] arg_data Pointer to valid data of type 'T_in'.
   */
  virtual void UpdateMarshal(char* arg_data);

  /**
   * Update
   * Update the display with a new value.
   *
   * @param[in] arg_newValue
   * New value to add to the display.
   */
  virtual void Update(T_in arg_newValue) = 0;

};

#endif // DISPLAYBASE_HPP

