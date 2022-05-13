/**
 * reference LICENSE file provided.
 *
 * @file CoreNode.hpp
 * Declarations for the CoreNode class.
 */

#ifndef CORENODE_HPP
#define CORENODE_HPP

// include: std.
#include <stdint.h>
#include <assert.h>
#include <iostream>
#include <vector>
#include <thread>
#include <atomic>

// include: app specific.
#include <NodePart/InputPipe/InputPipeBase.hpp>
#include <NodePart/OutputPipe/OutputPipeBase.hpp>
#include <NodePart/Processor/ProcessorBase.hpp>
#include <Message/Message.hpp>
#include <Message/MessageConstants.hpp>
#include <Exception/ErrorCode.hpp>
#include "IStorableNode.hpp"

/**
 * @class CoreNode
 * Asynchronous loop that continually:
 * - reads from the input pipe;
 * - performs a processing operation on the marshaled data; and
 * - sends that processed data out of an output pipe.
 */
template <class T_in, class T_out>
class CoreNode : public IStorableNode
{
public:

  /**
   * Constructs and starts a CoreNode instance.
   *
   * This instance takes ownership over the argument objects.
   *
   * @param[in] a_i Pointer to input pipe.
   * @param[in] a_p Pointer to processor.
   * @param[in] a_o Pointer to output pipe.
   */
  CoreNode(InputPipeBase* a_i, ProcessorBase<T_in, T_out>* a_p, OutputPipeBase* a_o);

  /**
   * Closes and destroys node members, releasing their resources.
   *
   * Ceases node operation.
   */
  ~CoreNode();

  /**
   * Satisfies base class.
   */
  IStorableNode::Type GetType()
  {
    return IStorableNode::Type::Core;
  }

  /**
   * Starts the node's looped operation.
   *
   * @param[in] arg_pThis Pointer to `this` instance.
   */
 static void S_NodeLoop(CoreNode<T_in, T_out>* arg_pThis);

private:
  
  // members: object.
  InputPipeBase*              _inPipe;
  ProcessorBase<T_in, T_out>* _proc;
  OutputPipeBase*             _outPipe;

  std::thread _nodeThread;
  std::atomic<bool> _isRunning;

};

#endif // CORENODE_HPP

