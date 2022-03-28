/*
 * reference LICENSE file provided.
 *
 * nodePs.hpp.
 *
 * Class declarations for ParamSets ('Ps') that define building Node
 * objects. The idea here is to implement a Builder pattern that lets
 * a client caller have an easy time instantiating Nodes, which can be
 * composed of a variety of components.
 *
 */

#ifndef NODEPS_HPP
#define NODEPS_HPP

class IStorableNode;

#include <NodePartBuilder/inPs.hpp>
#include <NodePartBuilder/outPs.hpp>
#include <NodePartBuilder/genPs.hpp>
#include <NodePartBuilder/procPs.hpp>
#include <NodePartBuilder/dispPs.hpp>

class nodePs
{
public:
  virtual ~nodePs() { } ;
  virtual IStorableNode* Make() = 0;
protected:
  nodePs() { } ;
};

template <class T_io>
class byteNodePs : public nodePs
{
public:
  byteNodePs(inPs* arg_inPs, outPs* arg_outPs)
  : _inPs(arg_inPs)
  , _outPs(arg_outPs)
  {
  }

  IStorableNode* Make();
private:
  inPs* _inPs;
  outPs* _outPs;
};

template <class T_in, class T_out>
class coreNodePs : public nodePs
{
public:
  coreNodePs
  ( inPs* arg_inPs
  , procPs<T_in, T_out>* arg_procPs
  , outPs* arg_outPs
  )
  : _inPs(arg_inPs)
  , _procPs(arg_procPs)
  , _outPs(arg_outPs)
  {
  }

  IStorableNode* Make();

private:
  inPs* _inPs;
  procPs<T_in, T_out>* _procPs;
  outPs* _outPs;
};

template <class T_out>
class sourceNodePs : public nodePs
{
public:
  sourceNodePs(genPs<T_out>* arg_genPs, outPs* arg_outPs)
  : _genPs(arg_genPs)
  , _outPs(arg_outPs)
  {
  }

  IStorableNode* Make();

private:
  genPs<T_out>* _genPs;
  outPs* _outPs;
};

template <class T_in>
class showNodePs : public nodePs
{
public:
  showNodePs(inPs* arg_inPs, dispPs<T_in>* arg_dispPs)
  : _inPs(arg_inPs)
  , _dispPs(arg_dispPs)
  {
  }

  IStorableNode* Make();

private:
  inPs* _inPs;
  dispPs<T_in>* _dispPs;
};

template <class T_in, class T_out>
class mixerNodePs : public nodePs
{
public:
  mixerNodePs
    ( inPs* arg_inPs1
    , inPs* arg_inPs2
    , outPs* arg_outPs
    )
    : _inPs1(arg_inPs1)
    , _inPs2(arg_inPs2)
    , _outPs(arg_outPs)
  {
  }

  IStorableNode* Make();

private:
  inPs* _inPs1;
  inPs* _inPs2;
  outPs* _outPs;
};

#endif // NODEPS_HPP

