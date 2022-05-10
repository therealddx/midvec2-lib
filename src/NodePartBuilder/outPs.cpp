/**
 * reference LICENSE file provided.
 *
 * @file outPs.cpp
 * Implements outPs.hpp
 *
 */

#include <NodePart/OutputPipe/OutputPipeBase.hpp>
#include <NodePart/OutputPipe/OutputPipeFile.hpp>
#include <NodePart/OutputPipe/OutputPipeUdp.hpp>
#include <NodePart/OutputPipe/OutputPipeRam.hpp>
#include "outPs.hpp"

OutputPipeBase* outFilePs::Make()
  { return new OutputPipeFile(_fqFile); }

OutputPipeBase* outUdpPs::Make()
  { return new OutputPipeUdp(_ipAddress, _port); }

OutputPipeBase* outRamPs::Make()
  { return new OutputPipeRam(_rb); }

