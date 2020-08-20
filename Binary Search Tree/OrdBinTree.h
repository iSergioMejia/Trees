#ifndef __PUJ__OrdBinTree__h__
#define __PUJ__OrdBinTree__h__

#include <string>

namespace PUJ
{
  template< class _TValue >
  class OrdBinTree
  {
  public:
    typedef _TValue    TValue;
    typedef OrdBinTree Self;

  protected:
    class Node
    {
    public:
      Node( const TValue& v );
      virtual ~Node( );

      const TValue& GetValue( ) const;

      bool IsLeaf( ) const;
      unsigned int Height( ) const;
      unsigned int Weight( ) const;

      void PrintInOrder( ) const;
      void PrintPreOrder( ) const;
      void PrintPostOrder( ) const;
      void PrintLevels( ) const;
      std::string PrintAsPNG( ) const;

      const Node* Find( const TValue& v ) const;

      Node* Insert( const TValue& v );

    public:
      TValue m_Value;
      Node*  m_Left;
      Node*  m_Right;
    };

  public:
    OrdBinTree( );
    virtual ~OrdBinTree( );

    bool Find( const TValue& v ) const;
    bool Insert( const TValue& v );
    
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

#include "OrdBinTree.hxx"

#endif // __PUJ__OrdBinTree__h__

// eof - OrdBinTree.h
