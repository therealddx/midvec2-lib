/*
 * reference LICENSE file provided.
 *
 * MixerNode.cpp.
 * Implements MixerNode.hpp.
 *
 */

#include <stdexcept>
#include <Types/Complex.hpp>
#include "MixerNode.hpp"

template <class T_in, class T_out>
MixerNode<T_in, T_out>::MixerNode
( InputPipeBase* arg_inPipe1
, InputPipeBase* arg_inPipe2
, OutputPipeBase* arg_outPipe
)
: _inPipe1(arg_inPipe1)
, _inPipe2(arg_inPipe2)
, _outPipe(arg_outPipe)
{
  // arg check.
  if (_inPipe1 == nullptr) { throw std::invalid_argument("arg_inPipe1"); }
  if (_inPipe2 == nullptr) { throw std::invalid_argument("arg_inPipe2"); }
  if (_outPipe == nullptr) { throw std::invalid_argument("arg_outPipe"); }

  _isRunning = true;
  _runThread = std::thread(&MixerNode<T_in, T_out>::S_Start, this);
}

template <class T_in, class T_out>
MixerNode<T_in, T_out>::~MixerNode()
{
  _isRunning = false;
  _inPipe1->Cancel();
  _inPipe2->Cancel();
  _outPipe->Cancel();
  _runThread.join();

  delete _inPipe1;
  delete _inPipe2;
  delete _outPipe;
}

template <class T_in, class T_out>
void MixerNode<T_in, T_out>::S_Start(MixerNode<T_in, T_out>* arg_pThis)
{
  // arg check.
  if (arg_pThis == nullptr) { return; }
  MixerNode<T_in, T_out>* pThis = arg_pThis;

  // running:
  while (pThis->_isRunning == true)
  {
    // get a value from the first input pipe.
    char* p_in1 = pThis->_inPipe1->GetMessage(sizeof(T_in));
    if (p_in1 == NULL) { continue; }
    Message<T_in> msg_in1(p_in1);

    // get a value from the second input pipe.
    char* p_in2 = pThis->_inPipe2->GetMessage(sizeof(T_in));
    if (p_in2 == NULL) { continue; }
    Message<T_in> msg_in2(p_in2);

    // multiply those two values.
    T_out mix_product = static_cast<T_out>(
      msg_in1.GetBacker() * msg_in2.GetBacker());

    // put that product out on the output pipe.
    Message<T_out> msg_mix_product(mix_product);
    char char_mix_product[msg_mix_product.GetRequiredSize()];
    msg_mix_product.GetBytes(char_mix_product);

    pThis->_outPipe->PutMessage(char_mix_product,
      msg_mix_product.GetRequiredSize());
  }

}

template class MixerNode<double, double>;
template class MixerNode<Complex<double>, Complex<double>>;

