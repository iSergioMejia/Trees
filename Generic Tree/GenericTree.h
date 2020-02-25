/*┌──────────────────────────────────────────────────────────────────────────────┐ 
**│Code made by Leonardo Florez Valencia                                         │
**│                                                                              │
**│Modified and completed by Sergio Mejía, Laura Jiménez and Sebastián Gutierrez │
**│for the Data Structures lesson 1830                                           │
**└──────────────────────────────────────────────────────────────────────────────┘ 
*/  
#ifndef __PUJ__GENERICTREE__H__
#define __PUJ__GENERICTREE__H__

#include <list>
#include <string>
#include <utility>

namespace PUJ
{
  /**
   */
  template< class T >
  class GenericTree
  {
  public:
    typedef T           TValue;
    typedef GenericTree Self;

  protected:
    class Node
    {
    public:
      typedef std::list< Node* > TChildren;

    public:
      Node( );
      virtual ~Node( );

      void BuildFromPreorder( std::istream& input );

      const T& GetValue( ) const;
      void SetValue( const T& v );
      void AddChild( const T& v );

      bool IsLeaf( ) const;
      bool IsSemiComplete( ) const;
      unsigned int Height( ) const;
      unsigned int Weight( ) const;
      unsigned int GlobalOrder() const;
      unsigned int Width( );// const;
      void PrintInOrder( ) const;

      //\!brief: Returns a vector with the values of the tree in inorder
      std::vector<int> GetInOrder( ) const;
      void PrintPreOrder( ) const;
      void PrintPostOrder( ) const;
      void PrintLevels( ); //const;
      std::string PrintAsPNG( ) const;

      //\!brief: Returns a pointer to the node with the value v
      Node* Find( const T& v );

      //\!brief: Returns a constant pointer to the node with the value v
      const Node* Find( const T& v ) const;

      //\!brief: Returns a constant vector of values from the Node to a given node value
      const std::vector <int> FindPath( const T& v );

      //\!brief: Returns a node const to the common ancestor of two given node values
      //This method asumes the two values exist in the tree and are not duplicated
      Node* const CommonAncestor(const T& v1, const T& v2);

      //\!brief: Returns a vector of values of the path between two node values
      //This method asumes the two values exist in the tree and are not duplicated
      std::vector <int> PathBetweenTwoNodes(const T& v1, const T& v2) ;//const;

      //\!brief: Returns a vector of constant node pointer of a given level of the tree
      std::vector <const Node*> LevelValues(unsigned int level, unsigned int thisLevel) const;

      //\!brief: Returns the number of times a value v appears in the tree
      unsigned int countRepeated(const T& v) const;

      //\!brief: Returns if two trees (this and the given by parameter) are isomorphic
      bool AreIsomorphic(const Node* otherTree) const;

      //\!brief: Returns if the tree contains the tree given by parameter
      bool IsContained(const Node* otherTree) const;

      //\!brief: Returns if the tree is an AVL Tree
      bool IsAVL();

      //\!brief: Returns if the tree is a Heap Tree
      bool IsHeap();

    protected:
      T         m_Value;
      TChildren m_Children;
    };

  public:
    GenericTree( );
    virtual ~GenericTree( );

    void BuildFromPreorder( std::istream& input );

    //\!brief: Returns if the given value v is in the tree
    bool Find( const T& v ) const;

    //\!brief: Returns a pointer to the value corresponding to the common ancestor between two nodes
    const T* CommonAncestor(const T& v1, const T& v2) const;

    //\!brief: Returns a vector containing the path between two node values
    std::vector <int> PathBetweenTwoNodes(const T& v1, const T& v2) const; 

    //\!brief: Prints a list of the velues of a given level in the designated order (true for Left to Right, false for Right to Left)
    void LevelValues(unsigned int level, bool LROrder); 

    //\!brief: Returns the number of times a value v appears in the tree
    unsigned int countRepeated(const T& v) const;

    //\!brief: Returns a vector with all the repeated values in the tree (this is, that the value appears more than 1 time)
    std::vector <int> getRepeatedValues();

    //\!brief: Returns if the tree contains the tree given by parameter
    bool IsContained(const Self& otherTree) const;

    //\!brief: Returns if the tree is an AVL Tree
    bool IsAVL();

    //\!brief: Returns if the tree is a Heap Tree
    bool IsHeap();

    //\!brief: Returns if two trees (this and the given by parameter) are isomorphic
    bool AreIsomorphic(const Self& otherTree) const;

    unsigned int Height( ) const;
    unsigned int Weight( ) const;
    unsigned int GlobalOrder( ) const;
    unsigned int Width( ) const;
    void PrintInOrder( ) const;
    void PrintPreOrder( ) const;
    void PrintPostOrder( ) const;
    void PrintLevels( ) const;
    void PrintAsPNG( const std::string& filename ) const;

  protected:
    Node* m_Root;
  };

} // ecapseman

#include "GenericTree.hxx"

#endif // __PUJ__GENERICTREE__H__

// eof - GenericTree.h
