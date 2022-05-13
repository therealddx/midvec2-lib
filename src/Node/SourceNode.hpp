/**
 * reference LICENSE file provided.
 *
 * @file SourceNode.hpp
 *
 * Declarations for the SourceNode class.
 *
 */

#ifndef SOURCENODE_HPP
#define SOURCENODE_HPP

#include <atomic>
#include <thread>
#include <functional>
#include <Message/MessageConstants.hpp>
#include <Message/Message.hpp>
#include <NodePart/Generator/GeneratorBase.hpp>
#include <NodePart/OutputPipe/OutputPipeBase.hpp>
#include "IStorableNode.hpp"

/**
 * @class SourceNode
 *
 * Asynchronous loop that continually:
 * - generates a value; and
 * - sends that value out of its output pipe.
 *
 */
template <class T_out>
class SourceNode : public IStorableNode
{
public:

  /**
   * SourceNode
   *
   * Constructs and starts a SourceNode instance.
   *
   * This instance takes ownership over the argument objects.
   *
   * @param[in] a_g Pointer to generator.
   * @param[in] a_o Pointer to output pipe.
   */
  SourceNode(GeneratorBase<T_out>* a_g, OutputPipeBase* a_o);

  /**
   * ~SourceNode
   *
   * Closes and destroys node members; releasing their resources.
   *
   * Ceases node operation.
   */
  ~SourceNode();

  /**
   * GetType
   *
   * Satisfies base class.
   */
  IStorableNode::Type GetType()
  {
    return IStorableNode::Type::Source;
  }

  /**
   * S_Start
   *
   * Starts the node's looped operation.
   *
   * @param[in] arg_pThis Pointer to 'this' instance.
   */
  static void S_Start(SourceNode<T_out>* arg_pThis);

private:
  
  // members: object.
  GeneratorBase<T_out>* _generator;
  OutputPipeBase* _outPipe;

  // members: threading.
  std::atomic<bool> _isRunning;
  std::thread _runThread;
};

#endif // SOURCENODE_HPP

