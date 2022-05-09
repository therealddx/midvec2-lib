/**
 * reference LICENSE file provided.
 *
 * @file MixerNode.hpp
 * Asynchronous loop that continually:
 *   reads from one input pipe;
 *   reads from a second input pipe;
 *   multiplies the two signals' values; and
 *   sends that product of signals out of the output pipe.
 *
 */

#ifndef MIXERNODE_HPP
#define MIXERNODE_HPP

#include <thread>
#include <atomic>
#include <NodePart/InputPipe/InputPipeBase.hpp>
#include <NodePart/OutputPipe/OutputPipeBase.hpp>
#include <Message/Message.hpp>
#include <Message/MessageConstants.hpp>
#include "IStorableNode.hpp"

/**
 * @class MixerNode
 */
template <class T_in, class T_out>
class MixerNode : public IStorableNode
{
public:

  /**
   * MixerNode
   *
   * Starts the node.
   *
   * This instance takes ownership over the argument objects.
   *
   * @param[in] a_i1 Pointer to first input pipe.
   * @param[in] a_i2 Pointer to second input pipe.
   * @param[in] a_o Pointer to output pipe.
   */
  MixerNode(InputPipeBase* a_i1, InputPipeBase* a_i2, OutputPipeBase* a_o);

  /**
   * ~MixerNode
   *
   * Closes and destroys node members; releasing their resources.
   * Ceases node operation.
   */
  ~MixerNode();

  /**
   * GetType
   * Satisfies base class.
   */
  IStorableNode::Type GetType()
  {
    return IStorableNode::Type::Mixer;
  }

  /**
   * S_Start
   * Starts the node's looped operation.
   *
   * @param[in] arg_pThis Pointer to 'this' instance.
   */
  static void S_Start(MixerNode<T_in, T_out>* arg_pThis);

private:

  InputPipeBase* _inPipe1;
  InputPipeBase* _inPipe2;
  OutputPipeBase* _outPipe;

  std::thread _runThread;
  std::atomic<bool>_isRunning;

};

#endif // MIXERNODE_HPP

