/*
 * reference LICENSE file provided.
 * 
 * ByteNode.cpp.
 * Implements ByteNode.hpp.
 * 
 */

#include <stdexcept>
#include <Message/MessageConstants.hpp>
#include <Message/Message.hpp>
#include <Types/Complex.hpp>
#include "ByteNode.hpp"

template <class T>
ByteNode<T>::ByteNode
( InputPipeBase*  arg_inPipe
, OutputPipeBase* arg_outPipe )
: _inPipe(arg_inPipe)
, _outPipe(arg_outPipe)
{
  // arg check.
  if (_inPipe == nullptr) { throw std::invalid_argument("arg_inPipe"); }
  if (_outPipe == nullptr) { throw std::invalid_argument("arg_outPipe"); }

  _runThread = std::thread(&ByteNode<T>::S_Start, this);
}

template <class T>
ByteNode<T>::~ByteNode()
{
  _isRunning = false;
  _runThread.join();

  delete _inPipe;
  delete _outPipe;
}

template <class T>
void ByteNode<T>::S_Start(ByteNode<T>* pThis)
{
  pThis->_isRunning = true;

  while (pThis->_isRunning == true)
  {
    // fwif => char*.
    char* p_midv_message = pThis->_inPipe->GetMessage(sizeof(T));

    // null-check.
    if (p_midv_message == NULL) { continue; }

    // make the 'char*' into a 'T'.
    Message<T> msg(p_midv_message);

    // char* => fwif.
    pThis->_outPipe->PutMessage(p_midv_message, msg.GetRequiredSize());
  }
}

template class ByteNode<double>;
template class ByteNode<Complex<double>>;

