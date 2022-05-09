/**
 * reference LICENSE file provided.
 *
 * @file GeneratorBase.hpp
 * Abstract class representing the ability to generate new values.
 *
 */

#ifndef GENERATORBASE_HPP
#define GENERATORBASE_HPP

/**
 * @class GeneratorBase
 */
template <class T_out>
class GeneratorBase
{
public:

  /**
   * GeneratorBase
   */
  GeneratorBase() { } ;

  /**
   * ~GeneratorBase
   */
  virtual ~GeneratorBase() { } ;

  /**
   * NextMarshal
   * Generate a new value of the type 'T_out', and store it in the pointer argument.
   *
   * @param[in] rtn_data
   * Location to store the generated value.
   */
  virtual void NextMarshal(char*& rtn_data);

  /**
   * Next
   * Generate a new value of type 'T_out', IAW the type of the generator.
   * @return New, generated value of type 'T_out'.
   */
  virtual T_out Next() = 0;

};

#endif // GENERATORBASE_HPP

