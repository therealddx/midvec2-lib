/*
 * reference LICENSE file provided.
 *
 * TestDisplayGraph.cpp.
 *
 * Implements TestDisplayGraph.hpp.
 *
 */

// include: midvec library.
//
#include <Application/TestDisplayGraph/TestGraphGlui.hpp>
#include <NodePartBuilder/dispPs.hpp>

// include: header.
//
#include "TestDisplayGraph.hpp"

void TestDisplayGraph()
{
  // declare + define DisplayGraph components.
  //
  TestGraphGlui* myGlui = new TestGraphGlui("tdg.txt");

  // use dispGraphPs to make the DisplayGraph.
  // 
  dispGraphPs<double>* myDispGraphPs = new dispGraphPs<double>(myGlui);

  // construct a DisplayGraph.
  //
  DisplayBase<double>* myDisplayGraph = myDispGraphPs->Make();

  // the DisplayGraph has initialized it into its system.
  // can now show my plot.
  // 
  myGlui->Show();

  // push values in.
  //
  double testDelta = 0.05;
  for (double testUpdate = -1.0; testUpdate < 11.0; testUpdate += 0.01)
  {
    myDisplayGraph->Update(testUpdate);
  }
}

