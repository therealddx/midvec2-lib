/*
 * reference LICENSE file provided.
 *
 * DisplayGraph.hpp.
 * Implements a graph view of a discrete-time signal.
 *
 */

#ifndef DISPLAYGRAPH_HPP
#define DISPLAYGRAPH_HPP

#include <stdint.h>
#include <stdexcept>
#include <vector>
#include <Types/RingBuffer.hpp>
#include "DisplayBase.hpp"
#include "GraphGluiBase.hpp"

template <class T_in>
class DisplayGraph : public DisplayBase<T_in>
{
public:

  DisplayGraph(GraphGluiBase<uint32_t, T_in>*);
  ~DisplayGraph();

  void Update(T_in);

private:

  GraphGluiBase<uint32_t, T_in>* _guiGlue;
  uint32_t _sampleCount;
};

#endif // DISPLAYGRAPH_HPP

