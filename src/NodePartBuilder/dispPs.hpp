/**
 * reference LICENSE file provided.
 *
 * @file dispPs.hpp
 * Represents the set of parameters-- 'parameter set', or 'ps'--
 *   that contruct subclasses of DisplayBase.
 *
 */

#ifndef DISPPS_HPP
#define DISPPS_HPP

// include: c/c++ standard library.
#include <stdint.h>
#include <string>

// include: midvec library.
#include <NodePart/Display/DisplayBase.hpp>
#include <Types/RingBuffer.hpp>

/**
 * @class dispPs
 * Base class for parameter sets of DisplayBase.
 */
template <class T_in>
class dispPs
{
public:

  /**
   * ~dispPs
   */
  virtual ~dispPs() { } ;

  /**
   * Make
   * Subclasses are guaranteed to construct a subclass of DisplayBase.
   * @return Instance of DisplayBase.
   */
  virtual DisplayBase<T_in>* Make() = 0;

protected:
  dispPs() { } ;
};

/**
 * @class dispFilePs
 * Class representing the parameters for constructing a DisplayFile.
 */
template <class T_in>
class dispFilePs : public dispPs<T_in>
{
public:

  /**
   * dispFilePs
   * Stores DisplayFile constructor arguments, for construction by Make.
   * @param[in] arg_fqFile Fully-qualified path to file.
   */
  dispFilePs(std::string arg_fqFile) : _fqFile(arg_fqFile) { } ;

  /**
   * Make
   * Satisfies base class.
   */
  DisplayBase<T_in>* Make();

private:
  std::string _fqFile;
};

#endif // DISPPS_HPP

