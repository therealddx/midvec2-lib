/* 
 * reference LICENSE file provided.
 *
 * CoreNode.hpp.
 * Serves features of Node<T>, plus ability to perform a processing
 * function on obtained vectors of type T.
 *
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

template <class T_in, class T_out>
class CoreNode : public IStorableNode
{
public:

  // 
  // Ctor.
  // Assigns and constructs members.
  // Starts operation.
  //
  CoreNode<T_in, T_out>
    ( InputPipeBase*              arg_inPipe
    , ProcessorBase<T_in, T_out>* arg_proc
    , OutputPipeBase*             arg_outPipe
    );

  // 
  // Dtor.
  // Destroys and frees members.
  // Stops operation.
  //
  ~CoreNode<T_in, T_out>();

  // 
  // GetType.
  // Answers for the type of node this is.
  //
  IStorableNode::Type GetType() { return IStorableNode::Type::Core; }

  // 
  // S_NodeLoop.
  // Primary thread for Node operation.
  // Outputs processed vectors on loop.
  //
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

