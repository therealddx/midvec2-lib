/**
 * reference LICENSE file provided.
 *
 * @file inPs.cpp
 * Implements inPs.hpp
 *
 */

#include <NodePart/InputPipe/InputPipeBase.hpp>
#include <NodePart/InputPipe/InputPipeFile.hpp>
#include <NodePart/InputPipe/InputPipeUdp.hpp>
#include <NodePart/InputPipe/InputPipeRam.hpp>
#include "inPs.hpp"

InputPipeBase* inFilePs::Make()
  { return new InputPipeFile(_fqFile); }

InputPipeBase* inUdpPs::Make()
  { return new InputPipeUdp(_ipv4_bind, _port); }

InputPipeBase* inRamPs::Make()
  { return new InputPipeRam(_rb); }

