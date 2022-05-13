/**
 * reference LICENSE file provided.
 *
 * @file nodePs.hpp
 * Declarations for:
 * - nodePs
 * - byteNodePs
 * - coreNodePs
 * - sourceNodePs
 * - showNodePs
 * - mixerNodePs
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
 * Base class for representing a group of arguments that can construct nodes--
 *   a "parameter set", hence "ps".
 */
class nodePs
{
public:

  /**
   * Destroys this instance, and the subclass.
   */
  virtual ~nodePs() { } ;

  /**
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
   * Stores ByteNode constructor arguments, for construction by `Make`.
   *
   * @param[in] arg_inPs Parameter set for InputPipeBase.
   * @param[in] arg_outPs Parameter set for OutputPipeBase.
   */
  byteNodePs(inPs* arg_inPs, outPs* arg_outPs)
  : _inPs(arg_inPs)
  , _outPs(arg_outPs)
  {
  }

  /**
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
   * Stores CoreNode constructor arguments, for construction by `Make`.
   *
   * @param[in] arg_inPs Parameter set for InputPipeBase.
   * @param[in] arg_procPs Parameter set for ProcessorBase.
   * @param[in] arg_outPs Parameter set for OutputPipeBase.
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
   * Stores SourceNode constructor arguments, for construction by `Make`.
   *
   * @param[in] arg_genPs Parameter set for GeneratorBase.
   * @param[in] arg_outPs Parameter set for OutputPipeBase.
   */
  sourceNodePs(genPs<T_out>* arg_genPs, outPs* arg_outPs)
  : _genPs(arg_genPs)
  , _outPs(arg_outPs)
  {
  }

  /**
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
   * Stores ShowNode constructor arguments, for construction by `Make`.
   *
   * @param[in] arg_inPs Parameter set for InputPipeBase.
   * @param[in] arg_dispPs Parameter set for DisplayBase.
   */
  showNodePs(inPs* arg_inPs, dispPs<T_in>* arg_dispPs)
  : _inPs(arg_inPs)
  , _dispPs(arg_dispPs)
  {
  }

  /**
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
   * Stores MixerNode constructor arguments, for construction by `Make`.
   *
   * @param[in] arg_inPs1 Parameter set for first InputPipeBase.
   * @param[in] arg_inPs2 Parameter set for second InputPipeBase.
   * @param[in] arg_outPs Parameter set for OutputPipeBase.
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
   * Satisfies base class.
   */
  IStorableNode* Make();

private:
  inPs* _inPs1;
  inPs* _inPs2;
  outPs* _outPs;
};

#endif // NODEPS_HPP

