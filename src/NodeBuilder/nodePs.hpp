/**
 * reference LICENSE file provided.
 *
 * @file nodePs.hpp
 * Represents the set of parameters-- 'parameter set', or 'ps'--
 *   that construct nodes.
 *
 */

#ifndef NODEPS_HPP
#define NODEPS_HPP

class IStorableNode;

#include <NodePartBuilder/inPs.hpp>
#include <NodePartBuilder/outPs.hpp>
#include <NodePartBuilder/genPs.hpp>
#include <NodePartBuilder/procPs.hpp>
#include <NodePartBuilder/dispPs.hpp>

/**
 * @class nodePs
 * Base class for constructing nodes from parameter sets.
 */
class nodePs
{
public:

  /**
   * ~nodePs
   */
  virtual ~nodePs() { } ;

  /**
   * Make
   * Subclasses are guaranteed to construct a subclass of IStorableNode.
   * @return Instance of IStorableNode.
   */
  virtual IStorableNode* Make() = 0;

protected:
  nodePs() { } ;
};

/**
 * @class byteNodePs
 * Class representing the parameters for constructing a ByteNode.
 */
template <class T_io>
class byteNodePs : public nodePs
{
public:

  /**
   * byteNodePs
   *
   * Stores ByteNode constructor arguments, for construction by Make.
   *
   * @param[in] arg_inPs Parameter set for input pipe.
   * @param[in] arg_outPs Parameter set for output pipe.
   */
  byteNodePs(inPs* arg_inPs, outPs* arg_outPs)
  : _inPs(arg_inPs)
  , _outPs(arg_outPs)
  {
  }

  /**
   * Make
   * Satisfies base class.
   */
  IStorableNode* Make();

private:
  inPs* _inPs;
  outPs* _outPs;
};

/**
 * @class coreNodePs
 * Class representing the parameters for constructing a CoreNode.
 */
template <class T_in, class T_out>
class coreNodePs : public nodePs
{
public:

  /**
   * coreNodePs
   *
   * Stores CoreNode constructor arguments, for construction by Make.
   *
   * @param[in] arg_inPs Parameter set for input pipe.
   * @param[in] arg_procPs Parameter set for processor.
   * @param[in] arg_outPs Parameter set for output pipe.
   */
  coreNodePs
  ( inPs* arg_inPs
  , procPs<T_in, T_out>* arg_procPs
  , outPs* arg_outPs
  )
  : _inPs(arg_inPs)
  , _procPs(arg_procPs)
  , _outPs(arg_outPs)
  {
  }

  /**
   * Make
   * Satisfies base class.
   */
  IStorableNode* Make();

private:
  inPs* _inPs;
  procPs<T_in, T_out>* _procPs;
  outPs* _outPs;
};

/**
 * @class sourceNodePs
 * Class representing the parameters for constructing a SourceNode.
 */
template <class T_out>
class sourceNodePs : public nodePs
{
public:

  /**
   * sourceNodePs
   *
   * Stores SourceNode constructor arguments, for construction by Make.
   *
   * @param[in] arg_genPs Parameter set for generator.
   * @param[in] arg_outPs Parameter set for output pipe.
   */
  sourceNodePs(genPs<T_out>* arg_genPs, outPs* arg_outPs)
  : _genPs(arg_genPs)
  , _outPs(arg_outPs)
  {
  }

  /**
   * Make
   * Satisfies base class.
   */
  IStorableNode* Make();

private:
  genPs<T_out>* _genPs;
  outPs* _outPs;
};

/**
 * @class showNodePs
 * Class representing the parameters for constructing a ShowNode.
 */
template <class T_in>
class showNodePs : public nodePs
{
public:

  /**
   * showNodePs
   *
   * Stores ShowNode constructor arguments, for construction by Make.
   *
   * @param[in] arg_inPs Parameter set for input pipe.
   * @param[in] arg_dispPs Parameter set for display.
   */
  showNodePs(inPs* arg_inPs, dispPs<T_in>* arg_dispPs)
  : _inPs(arg_inPs)
  , _dispPs(arg_dispPs)
  {
  }

  /**
   * Make
   * Satisfies base class.
   */
  IStorableNode* Make();

private:
  inPs* _inPs;
  dispPs<T_in>* _dispPs;
};

/**
 * @class mixerNodePs
 * Class representing the parameters for constructing a MixerNode.
 */
template <class T_in, class T_out>
class mixerNodePs : public nodePs
{
public:

  /**
   * mixerNodePs
   *
   * Stores MixerNode constructor arguments, for construction by Make.
   *
   * @param[in] arg_inPs1 Parameter set for first input pipe.
   * @param[in] arg_inPs2 Parameter set for second input pipe.
   * @param[in] arg_outPs Parameter set for output pipe.
   */
  mixerNodePs
    ( inPs* arg_inPs1
    , inPs* arg_inPs2
    , outPs* arg_outPs
    )
    : _inPs1(arg_inPs1)
    , _inPs2(arg_inPs2)
    , _outPs(arg_outPs)
  {
  }

  /**
   * Make
   * Satisfies base class.
   */
  IStorableNode* Make();

private:
  inPs* _inPs1;
  inPs* _inPs2;
  outPs* _outPs;
};

#endif // NODEPS_HPP

