/**
 * reference LICENSE file provided.
 *
 * @file GeneratorBase.hpp
 * Declarations for GeneratorBase
 *
 */

#ifndef GENERATORBASE_HPP
#define GENERATORBASE_HPP

/**
 * @class GeneratorBase
 * Abstract class representing the ability to generate new values.
 */
template <class T_out>
class GeneratorBase
{
public:

  /**
   * This class is pure-virtual--
   *   attempts to construct cause compile-time error.
   */
  GeneratorBase() { } ;

  /**
   * Destroys this instance, and the subclass.
   */
  virtual ~GeneratorBase() { } ;

  /**
   * Generate a new value of type `T_out`,
   *   in accordance with the subclass specification.
   * @return Newly generated value of type `T_out`.
   */
  virtual T_out Next() = 0;

};

#endif // GENERATORBASE_HPP

