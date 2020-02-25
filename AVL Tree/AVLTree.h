#ifndef __PUJ__AVLTree__h__
#define __PUJ__AVLTree__h__

#include <string>

namespace PUJ
{
  template< class _TValue >
  class AVLTree
  {
  public:
    typedef _TValue TValue;
    typedef AVLTree Self;

  protected:
    class Node
    {
    public:
      Node( const TValue& v );
      virtual ~Node( );

      const TValue& GetValue( ) const;

      Node* Insert( const TValue& v );
      Node* Erase( const TValue& v );
      Node* EraseLeaf(const _TValue& v );

      bool IsLeaf( ) const;
      unsigned int Height( ) const;
      unsigned int Weight( ) const;
      void PrintInOrder( ) const;
      void PrintPreOrder( ) const;
      void PrintPostOrder( ) const;
      void PrintLevels( ) const;
      std::string PrintAsPNG( ) const;

      const Node* Find( const TValue& v ) const;

      static Node* RotLeft( Node* x );
      static Node* RotRight( Node* x );
      static Node* RotLeftRight( Node* x );
      static Node* RotRightLeft( Node* x );

    public:
      TValue m_Value;
      Node*  m_Left;
      Node*  m_Right;
      long   m_Height;
    };

  public:
    AVLTree( );
    virtual ~AVLTree( );

    bool Insert( const TValue& v );
    bool Erase( const TValue& v );
    bool Find( const TValue& v ) const;

    unsigned int Height( ) const;
    unsigned int Weight( ) const;
    void PrintInOrder( ) const;
    void PrintPreOrder( ) const;
    void PrintPostOrder( ) const;
    void PrintLevels( ) const;
    void PrintAsPNG( const std::string& filename ) const;

  protected:
    Node* m_Root;
  };

} // ecapseman

#include "AVLTree.hxx"

#endif // __PUJ__AVLTree__h__

// eof - AVLTree.h
