/*
 * reference LICENSE file provided.
 *
 * MixerNode.hpp.
 * Represents the product of two signals.
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

template <class T_in, class T_out>
class MixerNode : public IStorableNode
{
public:

  MixerNode<T_in, T_out>
    ( InputPipeBase* arg_inPipe1
    , InputPipeBase* arg_inPipe2
    , OutputPipeBase* arg_outPipe
    );

  // 
  // Dtor.
  //
  ~MixerNode<T_in, T_out>();

  // 
  // GetType.
  // Answers for the type of node this is.
  //
  IStorableNode::Type GetType() { return IStorableNode::Type::Mixer; }

  // 
  // S_Start.
  // Static-function placeholder for starting function.
  //
  static void S_Start(MixerNode<T_in, T_out>*);

private:

  InputPipeBase* _inPipe1;
  InputPipeBase* _inPipe2;
  OutputPipeBase* _outPipe;

  std::thread _runThread;
  std::atomic<bool>_isRunning;

};

#endif // MIXERNODE_HPP

