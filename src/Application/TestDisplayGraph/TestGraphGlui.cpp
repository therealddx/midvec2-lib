/*
 * reference LICENSE file provided.
 *
 * TestGraphGlui.cpp.
 *
 * Implements TestGraphGlui.hpp.
 *
 */

#include <string>
#include <stdexcept>

#include "TestGraphGlui.hpp"

TestGraphGlui::TestGraphGlui(std::string arg_filename)
  : GraphGluiBase(1024)
{
  // setup members: 'picture' parameters.
  // 
  _width = 800;
  _height = 600;
  _xMin = 0.0;
  _xMax = 512;
  _yMin = 0.0;
  _yMax = 1.0;

  // setup members: talkout files.
  //
  _outputFile.open(arg_filename);
  _showFile.open(std::string("show-") + arg_filename);
  _dbgFile.open(std::string("dbg-") + arg_filename);
  
  // setup members: view data.
  //
  _xView = std::vector<unsigned int>(_xAxis->GetSize());
  _yView = std::vector<double>(_yAxis->GetSize());
  if (_xView.size() != _yView.size())
  {
    std::cerr
      << "TestGraphGlui::TestGraphGlui: x- and y-axes have different lengths"
      << std::endl;
    throw std::invalid_argument("_xAxis");
  }
}

TestGraphGlui::~TestGraphGlui()
{
  // delete talkout files.
  //
  _outputFile.close();
  _showFile.close();
  _dbgFile.close();
}

void TestGraphGlui::Show()
{
  // 'show' the window.
  // 
  _showFile << "# showing with window values: " << std::endl;
  _showFile << "#  view width: " << _width << std::endl;  
  _showFile << "#  minimum X: " << _xMin << std::endl;
  _showFile << "#  maximum X: " << _xMax << std::endl;
  _showFile << "# " << std::endl;
  _showFile << "#  view height: " << _height << std::endl;
  _showFile << "#  minimum Y: " << _yMin << std::endl;
  _showFile << "#  maximum Y: " << _yMax << std::endl;  
  _showFile << "# " << std::endl;
  _showFile << std::endl;
}

void TestGraphGlui::UpdateGraph(unsigned int arg_newX, double arg_newY)
{
  // call super.
  //
  GraphGluiBase::UpdateGraph(arg_newX, arg_newY);

  // get data into the view.
  //
  _xAxis->ReadObjects(_xView);
  _yAxis->ReadObjects(_yView);

  // plot every point you have.
  //
  for (unsigned int n = 0; n < _xView.size(); n++)
  {
    // output (x-val, y-val).
    //
    _outputFile << 
      "(x-val, y-val): " << 
        "(" << std::to_string(_xView[n]) << ", " << std::to_string(_yView[n]) << ")";
   
    // close line.
    //
    _outputFile << std::endl;
  }

  // delineate.
  //
  _outputFile << "# finished plotting new points." << std::endl;
}


