/*
 * reference LICENSE file provided.
 * 
 * procPs.cpp.
 * Implements procPs.hpp.
 *
 */

#include <Types/Complex.hpp>
#include <NodePart/Processor/ProcessorBase.hpp>
#include <NodePart/Processor/ProcessorConv.hpp>
#include <NodePart/Processor/ProcessorDc.hpp>
#include "procPs.hpp"

template <class T_in, class T_out>
ProcessorBase<T_in, T_out>* procConvPs<T_in, T_out>::Make()
  { return new ProcessorConv<T_in, T_out>(_hn); }

template <class T_in, class T_out>
ProcessorBase<T_in, T_out>* procDcPs<T_in, T_out>::Make()
  { return new ProcessorDc<T_in, T_out>(_dc); }

template class procPs<double, double>;
template class procPs<Complex<double>, Complex<double>>;

template class procConvPs<double, double>;
template class procConvPs<Complex<double>, Complex<double>>;

template class procDcPs<double, double>;
template class procDcPs<Complex<double>, Complex<double>>;

