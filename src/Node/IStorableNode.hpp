/**
 * reference LICENSE file provided.
 *
 * @file IStorableNode.hpp
 * Declarations for the IStorableNode class.
 */

#ifndef ISTORABLENODE_HPP
#define ISTORABLENODE_HPP

/**
 * @class IStorableNode
 * This class allows Nodes to be stored (and `delete`d) in the same collection.
 */
class IStorableNode
{
public:

  /**
   * Destroys this instance, and the subclass.
   */
  virtual ~IStorableNode() { } ;

  /**
   * @enum Type
   * Enumerated types for Nodes that may be created in this library.
   */
  enum class Type
  {
    /**
     * Enumerated Node type index for ByteNode.
     */
    Byte,

    /**
     * Enumerated Node type index for CoreNode.
     */
    Core,

    /**
     * Enumerated Node type index for MixerNode.
     */
    Mixer,

    /**
     * Enumerated Node type index for ShowNode.
     */
    Show,
    
    /**
     * Enumerated Node type index for SourceNode.
     */
    Source,
  };

  /**
   * Reports the type index of an inheriting Node class.
   *
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

