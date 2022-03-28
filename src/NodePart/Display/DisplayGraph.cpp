/*
 * reference LICENSE file provided.
 * 
 * DisplayGraph.cpp.
 * 
 */

#include <Types/Complex.hpp>
#include "DisplayGraph.hpp"

template <class T_in>
DisplayGraph<T_in>::DisplayGraph(GraphGluiBase<uint32_t, T_in>* arg_guiGlue)
  : _guiGlue(arg_guiGlue)
{
  // arg check.
  // 
  if (_guiGlue == nullptr)
    { throw std::invalid_argument("arg_guiGlue"); }
}

template <class T_in>
DisplayGraph<T_in>::~DisplayGraph()
{
  delete _guiGlue;
}

template <class T_in>
void DisplayGraph<T_in>::Update(T_in arg_newValue)
{
  // update the graph.
  // 
  _guiGlue->UpdateGraph(_sampleCount++, arg_newValue);
}

template class DisplayGraph<double>;
template class DisplayGraph<Complex<double>>;

