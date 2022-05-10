/**
 * reference LICENSE file provided.
 *
 * @file nodePs.cpp
 * Implements nodePs.hpp
 * 
 */

#include <Node/IStorableNode.hpp>
#include <Node/ByteNode.hpp>
#include <Node/CoreNode.hpp>
#include <Node/SourceNode.hpp>
#include <Node/ShowNode.hpp>
#include <Node/MixerNode.hpp>
#include <Types/Complex.hpp>
#include "nodePs.hpp"

template <class T_io>
IStorableNode* byteNodePs<T_io>::Make()
{
  return new ByteNode<T_io>(_inPs->Make(), _outPs->Make());
}

template <class T_in, class T_out>
IStorableNode* coreNodePs<T_in, T_out>::Make()
{
  return new CoreNode<T_in, T_out>
    ( _inPs->Make()
    , _procPs->Make()
    , _outPs->Make()
    );
}

template <class T_out>
IStorableNode* sourceNodePs<T_out>::Make()
{
  return new SourceNode<T_out>
    ( _genPs->Make()
    , _outPs->Make()
    );
}

template <class T_in>
IStorableNode* showNodePs<T_in>::Make()
{
  return new ShowNode<T_in>
    ( _inPs->Make()
    , _dispPs->Make()
    );
}

template <class T_in, class T_out>
IStorableNode* mixerNodePs<T_in, T_out>::Make()
{
  return new MixerNode<T_in, T_out>
    ( _inPs1->Make()
    , _inPs2->Make()
    , _outPs->Make()
    );
}

template class byteNodePs<double>;
template class byteNodePs<Complex<double>>;

template class coreNodePs<double, double>;
template class coreNodePs<Complex<double>, Complex<double>>;

template class sourceNodePs<double>;
template class sourceNodePs<Complex<double>>;

template class showNodePs<double>;
template class showNodePs<Complex<double>>;

template class mixerNodePs<double, double>;
template class mixerNodePs<Complex<double>, Complex<double>>;

