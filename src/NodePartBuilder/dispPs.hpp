/*
 * reference LICENSE file provided.
 *
 * dispPs.hpp.
 * Class declarations to implement Builder pattern around subtypes of
 * DisplayBase.
 *
 */

#ifndef DISPPS_HPP
#define DISPPS_HPP

// include: c/c++ standard library.
#include <stdint.h>
#include <string>

// include: midvec library.
#include <NodePart/Display/DisplayBase.hpp>
#include <NodePart/Display/GraphGluiBase.hpp>
#include <Types/RingBuffer.hpp>

template <class T_in>
class dispPs
{
public:
  virtual ~dispPs() { } ;
  virtual DisplayBase<T_in>* Make() = 0;
protected:
  dispPs() { } ;
};

template <class T_in>
class dispFilePs : public dispPs<T_in>
{
public:
  dispFilePs(std::string arg_fqFile) : _fqFile(arg_fqFile) { } ;
  DisplayBase<T_in>* Make();

private:
  std::string _fqFile;
};

template <class T_in>
class dispGraphPs : public dispPs<T_in>
{
public:
  dispGraphPs(GraphGluiBase<uint32_t, T_in>* arg_guiGlue)
    : _guiGlue(arg_guiGlue)
  {
  }

  DisplayBase<T_in>* Make();

private:
  GraphGluiBase<uint32_t, T_in>* _guiGlue;
};

#endif // DISPPS_HPP

