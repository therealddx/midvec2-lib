/*
 * reference LICENSE file provided.
 * 
 * SourceNode.cpp.
 * Implements SourceNode.hpp.
 *
 */

#include <iostream>
#include <stdexcept>
#include <Types/Complex.hpp>
#include "SourceNode.hpp"

template <class T_out>
SourceNode<T_out>::SourceNode
  ( GeneratorBase<T_out>* arg_generator
  , OutputPipeBase* arg_outPipe
  )
  : _generator(arg_generator)
  , _outPipe(arg_outPipe)
{
  // arg check.
  if (_generator == nullptr) { throw std::invalid_argument("arg_generator"); }
  if (_outPipe == nullptr) { throw std::invalid_argument("arg_outPipe"); }

  _runThread = std::thread(&SourceNode<T_out>::S_Start, this);
}

template <class T_out>
SourceNode<T_out>::~SourceNode()
{
  _isRunning = false;
  _outPipe->Close();
  _runThread.join();

  delete _generator;
  delete _outPipe;
}

template <class T_out>
void SourceNode<T_out>::S_Start(SourceNode<T_out>* pThis)
{
  pThis->_isRunning = true;

  while (pThis->_isRunning == true)
  {
    // make T_out.
    T_out myT = pThis->_generator->Next();

    // frame the 'T_out' to a 'char*'.
    Message<T_out> to_put(myT);
    char to_put_char[to_put.GetRequiredSize()];
    to_put.GetBytes(to_put_char);

    // put T_out to the fwif.
    pThis->_outPipe->PutMessage(to_put_char, to_put.GetRequiredSize());
  }
}

template class SourceNode<double>;
template class SourceNode<Complex<double>>;

