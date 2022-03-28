/*
 * reference LICENSE file provided.
 *
 * IStorableNode.hpp.
 *
 * Unfortunately, this class is required so that Node objects that get instantiated
 * will have the ability to be stored in the same collection.
 *
 * What this means is that a higher-level executive will have a transparent interface
 * to storing and 'delete'ing Node objects when their resources are no longer needed.
 *
 */

#ifndef ISTORABLENODE_HPP
#define ISTORABLENODE_HPP

class IStorableNode
{
public:

  // 
  // dtor.
  // The core shared functionality among all Nodes is the
  // destructor; the ability to release resources upon delete.
  //
  virtual ~IStorableNode() { } ;

  // 
  // GetType.
  // Baked-in reflection information to travel down the inheritance tree.
  //
  enum class Type
  {
    Byte,
    Core,
    Mixer,
    Show,
    Source,
  };
  virtual Type GetType() = 0;

protected:

  // 
  // ctor.
  // 
  IStorableNode() { } ;
};

#endif // ISTORABLENODE_HPP

