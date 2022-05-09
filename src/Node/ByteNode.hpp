/**
 * reference LICENSE file provided.
 *
 * @file ByteNode.hpp
 * Asynchronous loop that continually:
 *   reads from the input pipe; and 
 *   sends the input pipe's data to the output pipe.
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

/**
 * @class ByteNode
 */
template <class T>
class ByteNode : public IStorableNode
{
public:

  /**
   * ByteNode
   * 
   * Starts the node.
   *
   * This instance takes ownership over the argument objects.
   *
   * @param[in] a_i Pointer to input pipe.
   * @param[in] a_o Pointer to output pipe.
   */
  ByteNode(InputPipeBase* a_i, OutputPipeBase* a_o);

  /**
   * ~ByteNode
   *
   * Closes and destroys node members; releasing their resources.
   * Ceases node operation.
   */
  ~ByteNode();

  /**
   * GetType
   * Satisfies base class.
   */
  IStorableNode::Type GetType()
  {
    return IStorableNode::Type::Byte;
  }

  /**
   * S_Start
   * Starts the node's looped operation.
   *
   * @param[in] arg_pThis Pointer to 'this' instance.
   */
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

