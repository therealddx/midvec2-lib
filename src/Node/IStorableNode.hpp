/**
 * reference LICENSE file provided.
 *
 * @file IStorableNode.hpp
 *
 * This class exists to allow Nodes to be stored in the same collection.
 * As such, they can be stored and `delete`d on loop.
 *
 */

#ifndef ISTORABLENODE_HPP
#define ISTORABLENODE_HPP

/**
 * @class IStorableNode
 */
class IStorableNode
{
public:

  /**
   * ~IStorableNode
   */
  virtual ~IStorableNode() { } ;

  /**
   * @enum Type
   * Enumerated types of Nodes that may be created in this library.
   */
  enum class Type
  {
    Byte,
    Core,
    Mixer,
    Show,
    Source,
  };

  /**
   * GetType
   * @return Enumerated value denoting the type of Node this is.
   */
  virtual Type GetType() = 0;

protected:

  // 
  // ctor.
  // 
  IStorableNode() { } ;
};

#endif // ISTORABLENODE_HPP

