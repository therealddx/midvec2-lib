/* 
 * reference LICENSE file provided.
 *
 * SourceNode.hpp.
 * Given templated type, outputs randomly-generated data along a:
 * - OutputPipeBase
 *
 * This randomly-generated data is designed to be readable by any
 * InputPipeBase.
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

template <class T_out>
class SourceNode : public IStorableNode
{
public:

  // 
  // Ctor. Uses GeneratorBase<T_out>.
  //
  SourceNode<T_out>
    ( GeneratorBase<T_out>* arg_generator
    , OutputPipeBase* arg_outPipe);

  // 
  // Dtor.
  // Destroys and frees members.
  // Stops operation.
  //
  ~SourceNode<T_out>();

  // 
  // GetType.
  // Answers for the type of node this is.
  //
  IStorableNode::Type GetType() { return IStorableNode::Type::Source; }

  // 
  // S_Start.
  // Static-function placeholder for kicking off the loop.
  //
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

