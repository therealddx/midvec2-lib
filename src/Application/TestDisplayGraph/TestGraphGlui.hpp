/*
 * reference LICENSE file provided.
 *
 * TestGraphGlui.hpp.
 *
 * Barebones implementation of GraphGluiBase to test ability to inherit the 
 * GraphGluiBase class, and then plot values as a result.
 *
 * Implements GraphGluiBase as an output filestream full of debug data, to
 * provide proof-of-concept on operation.
 *
 */

#ifndef TESTGRAPHGLUI_HPP
#define TESTGRAPHGLUI_HPP

// include: c/c++ library.
#include <fstream>

// include: midvec library.
#include <NodePart/Display/GraphGluiBase.hpp>

class TestGraphGlui : public GraphGluiBase<unsigned int, double>
{
public:
  TestGraphGlui(std::string arg_filename);
  ~TestGraphGlui();

  // methods: overridden from GraphGluiBase.
  //
  void UpdateGraph(unsigned int, double);

  // methods: useful for GUI-specific demonstration.
  //
  void Show();

private:

  // members: 'window' variables.
  //
  int _width;
  int _height;
  unsigned int _xMin;
  unsigned int _xMax;
  double _yMin;
  double _yMax;

  // members: talkout files.
  //
  std::ofstream _outputFile;
  std::ofstream _showFile;
  std::ofstream _dbgFile;

  // members: view data.
  //
  std::vector<unsigned int> _xView;
  std::vector<double> _yView;

};

#endif // TESTGRAPHGLUI_HPP

