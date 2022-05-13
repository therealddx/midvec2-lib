/**
 * reference LICENSE file provided.
 *
 * @file ShowNode.hpp
 *
 * Declarations for the ShowNode class.
 *
 */

#ifndef SHOWNODE_HPP
#define SHOWNODE_HPP

#include <stdint.h>
#include <iostream>
#include <string>
#include <thread>
#include <atomic>
#include <vector>
#include <Message/MessageConstants.hpp>
#include <Message/Message.hpp>
#include <NodePart/InputPipe/InputPipeBase.hpp>
#include <NodePart/Display/DisplayBase.hpp>
#include <Exception/ErrorCode.hpp>
#include "IStorableNode.hpp"

/**
 * @class ShowNode
 *
 * Asynchronous loop that continually:
 * - reads from the input pipe; and
 * - sends that input pipe data to a human-readable display.
 *
 */
template <class T_in>
class ShowNode : public IStorableNode
{
public:

  /**
   * ShowNode
   *
   * Constructs and starts a ShowNode instance.
   *
   * This instance takes ownership over the argument objects.
   *
   * @param[in] a_i Pointer to input pipe.
   * @param[in] a_d Pointer to display.
   */
  ShowNode(InputPipeBase* a_i, DisplayBase<T_in>* a_d);

  /**
   * ~ShowNode
   *
   * Closes and destroys node members; releasing their resources.
   *
   * Ceases node operation.
   */
  ~ShowNode();

  /**
   * GetType
   *
   * Satisfies base class.
   */
  IStorableNode::Type GetType()
  {
    return IStorableNode::Type::Show;
  }

  /**
   * S_Start
   *
   * Starts the node's looped operation.
   *
   * @param[in] arg_pThis Pointer to 'this' instance.
   */
  static void S_Start(ShowNode<T_in>* arg_pThis);

private:
  
  // members: object.
  InputPipeBase*      _inPipe;
  DisplayBase<T_in>*  _display;

  std::atomic<bool> _isRunning;
  std::thread _runThread;

};

#endif // SHOWNODE_HPP

