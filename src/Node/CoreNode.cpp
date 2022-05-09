/**
 * reference LICENSE file provided.
 *
 * @file CoreNode.cpp
 * Implements CoreNode.hpp
 *
 */

#include <stdexcept>
#include <Types/Complex.hpp>
#include "CoreNode.hpp"

template <class T_in, class T_out>
CoreNode<T_in, T_out>::CoreNode
  ( InputPipeBase*              arg_inPipe
  , ProcessorBase<T_in, T_out>* arg_proc
  , OutputPipeBase*             arg_outPipe
  )
  : _inPipe(arg_inPipe)
  , _proc(arg_proc)
  , _outPipe(arg_outPipe)
{
  // arg check.
  if (_inPipe == nullptr) { throw std::invalid_argument("arg_inPipe"); }
  if (_proc == nullptr) { throw std::invalid_argument("arg_proc"); }
  if (_outPipe == nullptr) { throw std::invalid_argument("arg_outPipe"); }

  _isRunning = true;
  _nodeThread = std::thread(&CoreNode<T_in, T_out>::S_NodeLoop, this);
}

template <class T_in, class T_out>
CoreNode<T_in, T_out>::~CoreNode()
{
  _isRunning = false;
  _inPipe->Close();
  _outPipe->Close();
  _nodeThread.join();

  delete _proc;
  delete _inPipe;
  delete _outPipe;
}

template <class T_in, class T_out>
void CoreNode<T_in, T_out>::S_NodeLoop(CoreNode<T_in, T_out>* arg_pThis)
{
  // arg check.
  if (arg_pThis == nullptr) { return; }
  CoreNode<T_in, T_out>* pThis = arg_pThis;

  // running:
  while (pThis->_isRunning == true)
  {
    // fwif => 'char*'.
    char* p_midv_message = pThis->_inPipe->GetMessage(sizeof(T_in));

    // null-check.
    if (p_midv_message == NULL) { continue; }

    // 'char*' => 'Message<T_in>'.
    Message<T_in> msg_in(p_midv_message);

    // 'Message<T_in>' => 'T_in' => 'T_out' => 'Message<T_out>'.
    // 
    T_out rn = pThis->_proc->Process(msg_in.GetBacker());
    Message<T_out> msg_out(rn);

    // 'Message<T_out>' => 'char*'.
    // 
    char msg_out_char[msg_out.GetRequiredSize()];
    msg_out.GetBytes(msg_out_char);

    // 'char*' => fwif.
    // 
    pThis->_outPipe->PutMessage(msg_out_char, msg_out.GetRequiredSize());
  }
}

template class CoreNode<double, double>;
template class CoreNode<Complex<double>, Complex<double>>;

