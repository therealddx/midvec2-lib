/*
 * reference LICENSE file provided.
 *
 * ByteNode.hpp.
 * Encapsulates usage of the following types:
 * - InputPipeBase
 * - OutputPipeBase
 *
 * Provides bare-minimum interface to their utilization:
 * - Incoming data is mathematically buffered: no processing
 * - Exists solely to translate data across I/O FW IFs.
 *
 */

#ifndef BYTENODE_HPP
#define BYTENODE_HPP

// include: thread.
#include <thread>
#include <atomic>

// include: app specific.
#include <NodePart/InputPipe/InputPipeBase.hpp>
#include <NodePart/OutputPipe/OutputPipeBase.hpp>
#include <Exception/ErrorCode.hpp>
#include "IStorableNode.hpp"

template <class T>
class ByteNode : public IStorableNode
{
public:

  // 
  // Ctor.
  // Assigns and constructs members.
  // Starts operation.
  //
  ByteNode<T>
    ( InputPipeBase*  arg_inPipe
    , OutputPipeBase* arg_outPipe
    );

  // 
  // Dtor.
  // Destroys and frees members.
  // Stops operation.
  //
  ~ByteNode<T>();

  // 
  // GetType.
  // Answers for the type of node this is.
  //
  IStorableNode::Type GetType() { return IStorableNode::Type::Byte; }

  // 
  // S_Start.
  // Static-function placeholder for kicking off the loop.
  //
  static void S_Start(ByteNode<T>* arg_pThis);

private:

  // 
  // members: object.
  //
  InputPipeBase*    _inPipe;
  OutputPipeBase*   _outPipe;

  std::atomic<bool> _isRunning;
  std::thread _runThread;

};

#endif // BYTENODE_HPP

