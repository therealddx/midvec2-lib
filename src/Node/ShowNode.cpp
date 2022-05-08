/* 
 * reference LICENSE file provided.
 * 
 * ShowNode.cpp.
 * Implements ShowNode.hpp.
 * 
 */

#include <stdexcept>
#include <Types/Complex.hpp>
#include "ShowNode.hpp"

template <class T_in>
ShowNode<T_in>::ShowNode
  ( InputPipeBase* arg_inPipe
  , DisplayBase<T_in>* arg_display
  )
  : _inPipe(arg_inPipe)
  , _display(arg_display)
{
  // arg check.
  if (_inPipe == nullptr) { throw std::invalid_argument("arg_inPipe"); }
  if (_display == nullptr) { throw std::invalid_argument("arg_display"); }

  // kick off thread.
  _isRunning = true;
  _runThread = std::thread(&ShowNode<T_in>::S_Start, this);
}

template <class T_in>
ShowNode<T_in>::~ShowNode()
{
  _isRunning = false;
  _inPipe->Close();
  _runThread.join();

  delete _display;
  delete _inPipe;
}

template <class T_in>
void ShowNode<T_in>::S_Start(ShowNode<T_in>* arg_pThis)
{
  // arg check.
  if (arg_pThis == nullptr) { return; }
  ShowNode<T_in>* pThis = arg_pThis;

  // running:
  while (pThis->_isRunning == true)
  {
    // fwif => char*.
    char* p_midv_message = pThis->_inPipe->GetMessage(sizeof(T_in));

    // null-check.
    if (p_midv_message == NULL) { continue; }

    // frame the 'char*' to a 'T_in'.
    Message<T_in> to_get(p_midv_message);

    // output to display.
    pThis->_display->Update(to_get.GetBacker());
  }
}

template class ShowNode<double>;
template class ShowNode<Complex<double>>;

