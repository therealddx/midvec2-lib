/**
 * reference LICENSE file provided.
 *
 * @file procPs.hpp
 * Represents the set of parameters-- 'parameter set', or 'ps'--
 *   that construct subclasses of ProcessorBase.
 *
 */

#ifndef PROCPS_HPP
#define PROCPS_HPP

#include <vector>
#include <NodePart/Processor/ProcessorBase.hpp>

/**
 * @class procPs
 * Base class for parameter sets of ProcessorBase.
 */
template <class T_in, class T_out>
class procPs
{
public:

  /**
   * ~procPs
   */
  virtual ~procPs() { } ;

  /**
   * Make
   * Subclasses are guaranteed to construct a subclass of ProcessorBase.
   * @return Instance of ProcessorBase.
   */
  virtual ProcessorBase<T_in, T_out>* Make() = 0;

protected:
  procPs() { } ;
};

/**
 * @class procConvPs
 * Class representing the parameters for constructing a ProcessorConv.
 */
template <class T_in, class T_out>
class procConvPs : public procPs<T_in, T_out>
{
public:

  /**
   * procConvPs
   * Stores ProcessorConv constructor arguments, for construction by Make.
   * @param[in] arg_hn Impulse response vector for convolution.
   */
  procConvPs(std::vector<T_in> arg_hn) : _hn(arg_hn) { } ;

  /**
   * Make
   * Satisfies base class.
   */
  ProcessorBase<T_in, T_out>* Make();

private:
  std::vector<T_in> _hn;
};

/**
 * @class procDcPs
 * Class representing the parameters for constructing a ProcessorDc.
 */
template <class T_in, class T_out>
class procDcPs : public procPs<T_in, T_out>
{
public:

  /**
   * procDcPs
   * Stores ProcessorDc constructor arguments, for construction by Make.
   * @param[in] arg_dc DC bias to apply to input signal.
   */
  procDcPs(T_in arg_dc) : _dc(arg_dc) { } ;

  /**
   * Make
   * Satisfies base class.
   */
  ProcessorBase<T_in, T_out>* Make();

private:
  T_in _dc;
};

#endif // PROCPS_HPP

