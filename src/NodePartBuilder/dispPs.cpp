/*
 * reference LICENSE file provided.
 * 
 * dispPs.cpp.
 * Implements dispPs.hpp.
 * 
 */

#include <Types/Complex.hpp>
#include <NodePart/Display/DisplayBase.hpp>
#include <NodePart/Display/DisplayFile.hpp>
#include "dispPs.hpp"

template <class T_in>
DisplayBase<T_in>* dispFilePs<T_in>::Make()
  { return new DisplayFile<T_in>(_fqFile); }

template class dispPs<double>;
template class dispPs<Complex<double>>;

template class dispFilePs<double>;
template class dispFilePs<Complex<double>>;

