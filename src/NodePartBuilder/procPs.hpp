/*
 * reference LICENSE file provided.
 *
 * procPs.hpp.
 * Class declarations to implement Builder pattern around objects of type
 * ProcessorBase.
 *
 */

#ifndef PROCPS_HPP
#define PROCPS_HPP

#include <vector>
#include <NodePart/Processor/ProcessorBase.hpp>

template <class T_in, class T_out>
class procPs
{
public:
  virtual ~procPs() { } ;
  virtual ProcessorBase<T_in, T_out>* Make() = 0;
protected:
  procPs() { } ;
};

template <class T_in, class T_out>
class procConvPs : public procPs<T_in, T_out>
{
public:
  procConvPs(std::vector<T_in> arg_hn) : _hn(arg_hn) { } ;
  ProcessorBase<T_in, T_out>* Make();
private:
  std::vector<T_in> _hn;
};

template <class T_in, class T_out>
class procDcPs : public procPs<T_in, T_out>
{
public:
  procDcPs(T_in arg_dc) : _dc(arg_dc) { } ;
  ProcessorBase<T_in, T_out>* Make();
private:
  T_in _dc;
};

#endif // PROCPS_HPP

