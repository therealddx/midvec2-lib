/*
 * reference LICENSE file provided.
 *
 * GraphGluiBase.hpp.
 *
 * In short, 'glues' a 'GUI' from a client application to this library.
 *
 * Client applications can inherit this class in order to tie the
 * functionality of DisplayGraph<T> to any concrete GUI that lives
 * outside of this library.
 *
 */

#ifndef GRAPHGLUIBASE_HPP
#define GRAPHGLUIBASE_HPP

#include <stdint.h>
#include <Types/RingBuffer.hpp>

template <class Tx, class Ty>
class GraphGluiBase
{
public:

  // ctor / dtor.
  //
  GraphGluiBase(uint32_t);
  virtual ~GraphGluiBase();

  // methods; public; virtual.
  //
  virtual void UpdateGraph(Tx, Ty);

protected:
  RingBuffer<Tx>* _xAxis;
  RingBuffer<Ty>* _yAxis;
};

template <class Tx, class Ty>
GraphGluiBase<Tx, Ty>::GraphGluiBase(uint32_t arg_axisLen)
{
  _xAxis = new RingBuffer<Tx>(arg_axisLen);
  _yAxis = new RingBuffer<Ty>(arg_axisLen);
}

template <class Tx, class Ty>
GraphGluiBase<Tx, Ty>::~GraphGluiBase()
{
  delete _xAxis;
  delete _yAxis;
}

template <class Tx, class Ty>
void GraphGluiBase<Tx, Ty>::UpdateGraph(Tx arg_newX, Ty arg_newY)
{
  // update the axes values.
  //   at the moment, not concerned with wait-delay for letting a reader catch up.
  //  
  _xAxis->Write(arg_newX); // push to x-pixel mapping.
  _yAxis->Write(arg_newY); // push to y-pixel mapping.
}

#endif // GRAPHGLUIBASE_HPP

