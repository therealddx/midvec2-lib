/* 
 * reference LICENSE file provided.
 *
 * ShowNode.hpp.
 * Takes templated data in via input pipe, and outputs it to a human-
 * readable tabulated format.
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

template <class T_in>
class ShowNode : public IStorableNode
{
public:

  // 
  // Ctor.
  // Assigns input pipe for display.
  //
  ShowNode<T_in>
    ( InputPipeBase* arg_inPipe
    , DisplayBase<T_in>* arg_display
    );

  // 
  // Dtor.
  // Releases class resources.
  //
  ~ShowNode<T_in>();

  // 
  // GetType.
  // Answers for the type of node this is.
  //
  IStorableNode::Type GetType() { return IStorableNode::Type::Show; }

  // 
  // S_Start.
  // static-function placeholder for initiating display loop.
  //
  static void S_Start(ShowNode<T_in>* arg_pThis);

private:
  
  // members: object.
  InputPipeBase*      _inPipe;
  DisplayBase<T_in>*  _display;

  std::atomic<bool> _isRunning;
  std::thread _runThread;

};

#endif // SHOWNODE_HPP

