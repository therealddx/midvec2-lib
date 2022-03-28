/*
 * reference LICENSE file provided.
 *
 * TestNodeBuilder.cpp.
 * Implements TestNodeBuilder.hpp.
 *
 * Methodology:
 * Setup:
 *  - Declare an IStorableNode*. This is the deletable client handle.
 *
 * Declare pointers to Builder pattern objects:
 *  - Declare and define parameter-set pointers for Node Parts.
 *  - Declare null paramset pointers for Nodes: one abstract, one concrete.
 * 
 * Verify Node creation:
 *  - With the concrete paramset pointer for Node:
 *   - Use it to make a concrete Node.
 *   - Ensure that the Node you just made is non-null.
 *   - Sleep one second (thread timing).
 *   - Delete-and-null the Node you just made.
 *  - With the abstract paramset pointer for Node:
 *   - Repeat the above steps.
 *
 * Evaluation:
 * Test PASSES if, and only if:
 *  All Node paramset pointers returned a non-null object reference on
 *  call to their 'Make' method.
 *
 */

#include <iostream>
#include <string>
#include <chrono>
#include <thread>

#include <NodeBuilder/nodePs.hpp>
#include <NodePartBuilder/genPs.hpp>

#include "TestNodeBuilder.hpp"

void sleep_1s()
{
  std::chrono::milliseconds dura(1000);
  std::this_thread::sleep_for(dura);
}

void Test_sourceNodePs()
{
  // opening print.
  std::cout << "Test_sourceNodePs:" << std::endl;

  // vars: storable node.
  //
  IStorableNode* my_SourceNode = nullptr;

  // vars: Builder pattern objects.
  //
  outPs* my_outPs = 
    new outFilePs(std::string("Test_sourceNodePs_outFile.txt"));
  genPs<double>* my_genPs = 
    new genSinePs<double>(0.0, 1.0, 0.0, 1.0, 1000);
  sourceNodePs<double>* my_sourceNodePs = nullptr;
  nodePs* my_nodePs = nullptr;

  // run: test creation of SourceNode with concrete class.
  //
  my_sourceNodePs = new sourceNodePs<double>(my_genPs, my_outPs);
  my_SourceNode = my_sourceNodePs->Make();
  std::cout << "sourceNodePs::Make: " << 
    (my_SourceNode != nullptr ? "OK" : "BAD") << std::endl;
  sleep_1s();
  delete my_SourceNode;
  my_SourceNode = nullptr;

  // run: test creation of SourceNode with abstract class.
  //
  my_nodePs = new sourceNodePs<double>(my_genPs, my_outPs);
  my_SourceNode = my_nodePs->Make();
  std::cout << "nodePs::Make: " << 
    (my_SourceNode != nullptr ? "OK" : "BAD") << std::endl;
  sleep_1s();
  delete my_SourceNode;
  my_SourceNode = nullptr;

  // closing print.
  std::cout << std::endl;
} 

void Test_byteNodePs()
{
  // opening print.
  std::cout << "Test_byteNodePs:" << std::endl;

  // vars: storable node.
  //
  IStorableNode* my_ByteNode = nullptr;

  // vars: Builder pattern objects.
  //
  inPs* my_inPs =
    new inFilePs(std::string("Test_byteNodePs_inFile.txt"));
  outPs* my_outPs =
    new outFilePs(std::string("Test_byteNodePs_outFile.txt"));
  byteNodePs<double>* my_byteNodePs = nullptr;
  nodePs* my_nodePs = nullptr;

  // run: test creation of ByteNode with concrete class.
  //
  my_byteNodePs = new byteNodePs<double>(my_inPs, my_outPs);
  my_ByteNode = my_byteNodePs->Make();
  std::cout << "byteNodePs::Make: " <<
    (my_ByteNode != nullptr ? "OK" : "BAD") << std::endl;
  sleep_1s();
  delete my_ByteNode;
  my_ByteNode = nullptr;

  // run: test creation of ByteNode with abstract class.
  //
  my_nodePs = new byteNodePs<double>(my_inPs, my_outPs);
  my_ByteNode = my_nodePs->Make();
  std::cout << "nodePs::Make: " << 
    (my_ByteNode != nullptr ? "OK" : "BAD") << std::endl;
  sleep_1s();
  delete my_ByteNode;
  my_ByteNode = nullptr;

  // closing print.
  std::cout << std::endl;
}

void TestNodeBuilder()
{
  Test_byteNodePs();

  Test_sourceNodePs();
}

