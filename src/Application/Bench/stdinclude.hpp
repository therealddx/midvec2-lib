#ifndef STDINCLUDE_HPP
#define STDINCLUDE_HPP

// C standard library.
// 
#include <cstdint>
#include <cstdlib>
#include <cstring>
#include <cstdio>

// C++ standard library.
// 
#include <iostream>
#include <fstream>
#include <ostream>
#include <string>
#include <vector>
#include <ios>
#include <sstream>
#include <iomanip>

// midvec-2 library.
// 
#include <Types/Complex.hpp>
#include <Message/MessageConstants.hpp>
#include <NodePartBuilder/inPs.hpp>
#include <NodePart/InputPipe/InputPipeFile.hpp>
#include <NodePart/InputPipe/InputPipeUdp.hpp>
#include <NodePart/InputPipe/InputPipeRam.hpp>
#include <Exception/ErrorCode.hpp>

// C sockets library.
// 
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

// C++ threading and real-time.
// 
#include <atomic>
#include <thread>
#include <chrono>

#endif // STDINCLUDE_HPP

