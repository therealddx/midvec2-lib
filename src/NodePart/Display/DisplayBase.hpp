/**
 * reference LICENSE file provided.
 *
 * @file DisplayBase.hpp
 * Declarations for DisplayBase
 */

#ifndef DISPLAYBASE_HPP
#define DISPLAYBASE_HPP

/**
 * @class DisplayBase
 * Defines an interface for displaying incoming data in human-readable form.
 */
template <class T_in>
class DisplayBase
{
public:

  /**
   * This class is pure-virtual--
   *   attempts to construct cause compile-time error.
   */
  DisplayBase() { } ;

  /**
   * Destroys this instance, and the subclass.
   */
  virtual ~DisplayBase() { } ;

  /**
   * Update the display with a new value.
   *
   * @param[in] arg_newValue
   * New value to add to the display.
   */
  virtual void Update(T_in arg_newValue) = 0;

};

#endif // DISPLAYBASE_HPP

