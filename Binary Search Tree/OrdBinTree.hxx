#ifndef __PUJ__OrdBinTree__hxx__
#define __PUJ__OrdBinTree__hxx__

#include <sstream>
#include <queue>
#include "OrdBinTree.h"

template<class _TValue>
PUJ::OrdBinTree<_TValue>::OrdBinTree()
{
    this->m_Root = NULL;   
}

template<class _TValue>
PUJ::OrdBinTree<_TValue>::Node::
Node( const TValue& v )
{
    this->m_Left = NULL;
    this->m_Right = NULL;
    this->m_Value = v;
}

template<class _TValue>
PUJ::OrdBinTree<_TValue>::~OrdBinTree()
{
    if(this->m_Root != NULL)
    {
        delete this->m_Root;
    }
}

template<class _TValue>
PUJ::OrdBinTree<_TValue>::Node::~Node()
{
    if(this->m_Left != NULL)
    {
        delete this->m_Left;
    } 
    if(this->m_Right != NULL)
    {
        delete this->m_Right;
    }
}

template<class _TValue>
const typename PUJ::OrdBinTree<_TValue>::TValue& PUJ::OrdBinTree< _TValue >::Node::
GetValue( ) const
{
    return (this->m_Value);
}

template<class _TValue>
typename PUJ::OrdBinTree< _TValue >::Node* PUJ::OrdBinTree< _TValue >::Node::
Insert( const TValue& v )
{
    if(this->m_Value < v)
    {
        if(this->m_Right != NULL)
            return(this->m_Right->Insert(v));
        else
        {
            this->m_Right = new Node(v);
            return (this->m_Right);
        }
    }
    else if(v < this->m_Value)
    {
        if(this->m_Left != NULL)
            return (this->m_Left->Insert(v));
        else
        {
            this->m_Left = new Node(v);
            return (this->m_Left);
        }
    }
    else
        return (NULL);
}

template<class _TValue>
bool PUJ::OrdBinTree< _TValue >::Insert( const TValue& v )
{
    if(this->m_Root != NULL)
        return(this->m_Root->Insert(v) != NULL);
    else
    {
        this->m_Root = new Node(v);
        return true;
    }

}

template<class _TValue>
bool PUJ::OrdBinTree< _TValue >::Node::IsLeaf( ) const
{
    if(this->m_Left == NULL && this->m_Right == NULL)
        return true;
    return false;
}

template<class _TValue>
const typename PUJ::OrdBinTree< _TValue >::Node* PUJ::OrdBinTree< _TValue >::Node::
Find( const TValue& v ) const
{
    if(this->m_Value < v)
    {
        if(this->m_Right != NULL)
            return (this->m_Right->Find(v));
        else return (NULL);
    }

    else if(v < this->m_Value)
    {
        if(this->m_Left != NULL)
            return (this->m_Left->Find(v));
        else return (NULL);
    }
    else
        return (this);
}

template<class _TValue>
bool PUJ::OrdBinTree< _TValue >::Find( const TValue& v ) const
{
    if(this->m_Root != NULL)
        return (this->m_Root->Find(v) != NULL);
    return false;
}

template<class _TValue>
unsigned int PUJ::OrdBinTree< _TValue >::Node::Weight( ) const
{
    unsigned int lw = 0, rw = 0;
    if(this->m_Left != NULL)
        lw = this->m_Left->Weight();
    if(this->m_Right != NULL)
        rw = this->m_Right->Weight();
    return (1 + lw + rw);
}

template<class _TValue>
unsigned int PUJ::OrdBinTree< _TValue >::Weight( ) const
{
    if(this->m_Root != NULL)
            return (this->m_Root->Weight());
    return 0;
}

// -------------------------------------------------------------------------

template<class _TValue>
unsigned int PUJ::OrdBinTree< _TValue >::Node::Height( ) const
{
    unsigned int hr = 0, hl = 0;
    if(this->m_Left != NULL)
        hl = this->m_Left->Height();
    if(this->m_Right != NULL)
        hr = this->m_Right->Height();
    return (1 + (hl>hr) ? hl : hr);
}

template<class _TValue>
unsigned int PUJ::OrdBinTree< _TValue >::Height( ) const
{
    if(this->m_Root != NULL)
            return (this->m_Root->Height());
    return 0;
}


// -------------------------------------------------------------------------
template< class _TValue >
void PUJ::OrdBinTree< _TValue >::Node::
PrintInOrder( ) const
{
	if(this->m_Left != NULL)
		this->m_Left->PrintInOrder();
	std::cout << (this->m_Value) << ", ";
	if(this->m_Right != NULL)
		this->m_Right->PrintInOrder();


	return;
}

//-------------------

template< class _TValue >
void PUJ::OrdBinTree< _TValue >::
PrintInOrder( ) const
{
	if(this->m_Root != NULL)
	{
		m_Root->PrintInOrder();
	}
	return;
}

// -------------------------------------------------------------------------
// -------------------------------------------------------------------------


template< class _TValue >
void PUJ::OrdBinTree< _TValue >::Node::
PrintPostOrder( ) const
{
	if(this->m_Left != NULL)
		this->m_Left->PrintPostOrder();
	if(this->m_Right != NULL)
		this->m_Right->PrintPostOrder();
	std::cout << (this->m_Value) << ", ";

	return;
}

//-------------------

template< class _TValue >
void PUJ::OrdBinTree< _TValue >::
PrintPostOrder( ) const
{
	if(this->m_Root != NULL)
	{
		m_Root->PrintPostOrder();
	}
	return;
}

// -------------------------------------------------------------------------
// -------------------------------------------------------------------------

template< class _TValue >
void PUJ::OrdBinTree< _TValue >::Node::
PrintPreOrder( ) const
{
	std::cout << (this->m_Value) << ", ";
	if(this->m_Left != NULL)
		this->m_Left->PrintPreOrder();
	if(this->m_Right != NULL)
		this->m_Right->PrintPreOrder();
	return;
}

//-------------------

template< class _TValue >
void PUJ::OrdBinTree< _TValue >::
PrintPreOrder( ) const
{
	if(this->m_Root != NULL)
	{
		m_Root->PrintPreOrder();
	}
	return;
}

template<class _TValue>
void PUJ::OrdBinTree< _TValue >::Node::
PrintLevels( ) const
{
	typedef PUJ::OrdBinTree< _TValue >::Node Nodo;
	std::queue <Nodo> auxQueue;
	auxQueue.push(*this);
	while( !auxQueue.empty() )
	{
		Nodo nodoActual = auxQueue.front(); auxQueue.pop();
		std::cout << nodoActual.m_Value << ", ";
		if(nodoActual.m_Left != NULL)
		{
			auxQueue.push( *(nodoActual.m_Left) );
		}
		if(nodoActual.m_Left != NULL)
		{
			auxQueue.push( *(nodoActual.m_Right) );
		}
	}
}

template<class _TValue>
void PUJ::OrdBinTree< _TValue >::
PrintLevels( ) const
{
	if(this->m_Root != NULL)
		this->m_Root->PrintLevels();
}

// -------------------------------------------------------------------------
template< class _TValue >
std::string PUJ::OrdBinTree< _TValue >::Node::
PrintAsPNG( ) const
{
  std::stringstream str;
  Node* nodes[ 2 ];
  nodes[ 0 ] = this->m_Left;
  nodes[ 1 ] = this->m_Right;

  for( unsigned int i = 0; i < 2; ++i )
  {
    if( nodes[ i ] != NULL )
    {
      str
        << ( unsigned long )( this ) << "->"
        << ( unsigned long )( nodes[ i ] ) << " "
        << ( unsigned long )( this )
        << " [label=" << this->m_Value << "]; "
        << ( unsigned long )( nodes[ i ] )
        << " [label=" << nodes[ i ]->m_Value << "]; "
        << nodes[ i ]->PrintAsPNG( );

    } // fi

  } // rof
  return( str.str( ) );
}

// -------------------------------------------------------------------------
template< class _TValue >
void PUJ::OrdBinTree< _TValue >::
PrintAsPNG( const std::string& filename ) const
{
  std::stringstream str;
  str << "echo \"digraph G{";
  if( this->m_Root != NULL )
  {
    if( this->m_Root->IsLeaf( ) )
      str << "\"" << this->m_Root->GetValue( ) << "\"";
    else
      str << this->m_Root->PrintAsPNG( );

  } // fi
  str << "}\" | dot -Tpng > " << filename;
  std::system( str.str( ).c_str( ) );
}

#endif // __PUJ__OrdBinTree__hxx__

// eof - OrdBinTree.hxx
