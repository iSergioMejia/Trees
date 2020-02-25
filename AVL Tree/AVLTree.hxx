#ifndef __PUJ__AVLTree__hxx__
#define __PUJ__AVLTree__hxx__

#include <iostream>
#include <queue>
#include <sstream>

// -------------------------------------------------------------------------
template< class _TValue >
PUJ::AVLTree< _TValue >::Node::
Node( const TValue& v )
: m_Value( v ),
m_Left( NULL ),
m_Right( NULL ),
m_Height( 1 )
{
}

// -------------------------------------------------------------------------
template< class _TValue >
PUJ::AVLTree< _TValue >::Node::
~Node( )
{
	if( this->m_Left != NULL )  delete this->m_Left;
	if( this->m_Right != NULL ) delete this->m_Right;
}

// -------------------------------------------------------------------------
template< class _TValue >
const _TValue& PUJ::AVLTree< _TValue >::Node::
GetValue( ) const
{
	return( this->m_Value );
}

// -------------------------------------------------------------------------
template< class _TValue >
typename PUJ::AVLTree< _TValue >::
Node* PUJ::AVLTree< _TValue >::Node::
Insert( const TValue& v )
{
	bool updated = true;
	if( v < this->m_Value )
	{
		if( this->m_Left == NULL )
		{
			this->m_Left = new Node( v );
			long h = ( this->m_Right != NULL )? this->m_Right->m_Height: 0;
			this->m_Height = 1 + ( ( 1 < h )? h: 1 );
		}
		else
		{
			Node* n = this->m_Left->Insert( v );
			if( n != NULL )
				this->m_Left = n;
			else
				updated = false;
    } // end if
  }
  else if( this->m_Value < v )
  {
  	if( this->m_Right == NULL )
  	{
  		this->m_Right = new Node( v );
  		long h = ( this->m_Left != NULL )? this->m_Left->m_Height: 0;
  		this->m_Height = 1 + ( ( 1 < h )? h: 1 );
  	}
  	else
  	{
  		Node* n = this->m_Right->Insert( v );
  		if( n != NULL )
  			this->m_Right = n;
  		else
  			updated = false;
    } // end if
  }
  else
  	updated = false;

  // Check rotations
  if( updated )
  {
  	Node* ret = this;
  	long b = ( this->m_Left != NULL )? this->m_Left->m_Height: 0;
  	b     -= ( this->m_Right != NULL )? this->m_Right->m_Height: 0;
  	if( b == -2 )
  	{
  		Node* n = this->m_Right;
  		long a = ( n->m_Left != NULL )? n->m_Left->m_Height: 0;
  		a     -= ( n->m_Right != NULL )? n->m_Right->m_Height: 0;
  		if( a == -1 )
  			ret = Node::RotLeft( this );
  		else if( a == 1 )
  			ret = Node::RotLeftRight( this );
  	}
  	else if( b == 2 )
  	{
  		Node* n = this->m_Left;
  		long a = ( n->m_Left != NULL )? n->m_Left->m_Height: 0;
  		a     -= ( n->m_Right != NULL )? n->m_Right->m_Height: 0;
  		if( a == -1 )
  			ret = Node::RotRightLeft( this );
  		else if( a == 1 )
  			ret = Node::RotRight( this );
  	}

    // Update ret's height and return it
  	long hl = ( ret->m_Left != NULL )? ret->m_Left->m_Height: 0;
  	long hr = ( ret->m_Right != NULL )? ret->m_Right->m_Height: 0;
  	ret->m_Height = 1 + ( ( hr < hl )? hl: hr );
  	return( ret );
  }
  else
  	return( NULL );
}

// -------------------------------------------------------------------------
template< class _TValue >
typename PUJ::AVLTree< _TValue >::
Node* PUJ::AVLTree< _TValue >::Node::
Erase( const TValue& v )
{
	if(v < this->m_Value) //ME VOY POR LEFT
	{
		if(this->m_Left != NULL)
		{
			if(this->m_Left->m_Value == v)
			{
				if(this->m_Left->IsLeaf()) //HOJA
				{
					delete(this->m_Left);
					this->m_Left = NULL;
				}
				else if(this->m_Left->m_Left == NULL)//TENGO HIJO DERECHO 
				{
					Node* temp = this->m_Left->m_Right;
					this->m_Left->m_Right = NULL;
					delete(this->m_Left->m_Right);
					this->m_Left = temp;
				}
				else if(this->m_Left->m_Right == NULL)//TENGO HIJO IZQUIERDO 
				{
					Node* temp = this->m_Left->m_Left;
					this->m_Left->m_Left = NULL;
					delete(this->m_Left->m_Left);
					this->m_Left = temp;	
				}
				else //DOS HIJOS
				{
					Node* z = this->m_Left->m_Right;
					while(z->m_Left != NULL)
						z = z->m_Left;
					std::swap(this->m_Left->m_Value, z->m_Value);
					this->m_Left->m_Right = this->m_Left->m_Right->Erase(z->m_Value);
				}
			}
			else this->m_Left = this->m_Left->Erase( v );
		}
		else return this;
	} 
	else if(this->m_Value < v)//ME VOY POR RIGHT
	{
		if(this->m_Right != NULL)
		{
			if(this->m_Right->m_Value == v)
			{
				if(this->m_Right->IsLeaf()) //HOJA
				{
					delete(this->m_Right);
					this->m_Right = NULL;
				}
				else if(this->m_Right->m_Left == NULL)//TENGO HIJO DERECHO 
				{
					Node* temp = this->m_Right->m_Right;
					//*(this->m_Right) = *temp;
					//free(temp);
					this->m_Right->m_Right = NULL;
					delete(this->m_Right->m_Right);
					this->m_Right = temp;
				}
				else if(this->m_Right->m_Right == NULL)//TENGO HIJO IZQUIERDO 
				{
					Node* temp = this->m_Right->m_Left;
					this->m_Right->m_Left = NULL;
					delete(this->m_Right->m_Left);
					this->m_Right = temp;
				}
				else //DOS HIJOS
				{
					Node* z = this->m_Right->m_Right;
					while(z->m_Left != NULL)
						z = z->m_Left;
					std::swap(this->m_Right->m_Value, z->m_Value);
					this->m_Right->m_Right = this->m_Right->m_Right->Erase(z->m_Value);
				}
			}
			else this->m_Right = this->m_Right->Erase( v );
		}
		else return this;
	}   
	else //CASO RAIZ
	{
		if(this->IsLeaf())
		{
			delete(this);
			return(NULL);
		}
		else if(this->m_Right == NULL) //HIJO IZQUIERDO
		{
			std::swap(this->m_Value, this->m_Left->m_Value);
			delete(this->m_Left);
			this->m_Left = NULL;
		}
		else if(this->m_Left == NULL) //HIJO DERECHO
		{
			std::swap(this->m_Value, this->m_Right->m_Value);
			delete(this->m_Right);
			this->m_Right = NULL;
		}	
		else //DOS HIJOS
		{
			Node* z = this->m_Right;
			while(z->m_Left != NULL)
				z = z->m_Left;
			std::swap(this->m_Value, z->m_Value);
			this->m_Right = this->m_Right->Erase(z->m_Value);
		}
	}

	if(this == NULL)
		return this;

	//UPDATE
  
	long hl = ( this->m_Left != NULL )? this->m_Left->m_Height: 0;
  long hr = ( this->m_Right != NULL )? this->m_Right->m_Height: 0;
  this->m_Height = 1 + ( ( hr < hl )? hl: hr );
 	long b = ( this->m_Left != NULL )? this->m_Left->m_Height: 0;
 	b     -= ( this->m_Right != NULL )? this->m_Right->m_Height: 0;
 	if( b == -2 )
 	{
 		Node* n = this->m_Right;
 		long a = ( n->m_Left != NULL )? n->m_Left->m_Height: 0;
 		a     -= ( n->m_Right != NULL )? n->m_Right->m_Height: 0;
 		if( a == -1 )
			return(Node::RotLeft( this ));
 		else if( a == 1 )
 			return(Node::RotLeftRight( this ));
 	}
 	else if( b == 2 )
 	{
 		Node* n = this->m_Left;
 		long a = ( n->m_Left != NULL )? n->m_Left->m_Height: 0;
 		a     -= ( n->m_Right != NULL )? n->m_Right->m_Height: 0;
 		if( a == -1 )
 			return(Node::RotRightLeft( this ));
 		else if( a == 1 )
 		{
 			return(Node::RotRight( this ));	
 		}
 			
 	}

  return (this);
}

// -------------------------------------------------------------------------
template< class _TValue >
bool PUJ::AVLTree< _TValue >::Node::
IsLeaf( ) const
{
	return( this->m_Left == NULL && this->m_Right == NULL );
}

// -------------------------------------------------------------------------
template< class _TValue >
unsigned int PUJ::AVLTree< _TValue >::Node::
Height( ) const
{
	return( this->m_Height );
}

// -------------------------------------------------------------------------
template< class _TValue >
unsigned int PUJ::AVLTree< _TValue >::Node::
Weight( ) const
{
	unsigned int l = ( this->m_Left != NULL )? this->m_Left->Weight( ): 0;
	unsigned int r = ( this->m_Right != NULL )? this->m_Right->Weight( ): 0;
	return( 1 + l + r );
}

// -------------------------------------------------------------------------
template< class _TValue >
void PUJ::AVLTree< _TValue >::Node::
PrintInOrder( ) const
{
	if( this->m_Left != NULL ) this->m_Left->PrintInOrder( );
	std::cout << this->m_Value << " ";
	if( this->m_Right != NULL ) this->m_Right->PrintInOrder( );
}

// -------------------------------------------------------------------------
template< class _TValue >
void PUJ::AVLTree< _TValue >::Node::
PrintPreOrder( ) const
{
	std::cout << this->m_Value << " ";
	if( this->m_Left != NULL ) this->m_Left->PrintPreOrder( );
	if( this->m_Right != NULL ) this->m_Right->PrintPreOrder( );
}

// -------------------------------------------------------------------------
template< class _TValue >
void PUJ::AVLTree< _TValue >::Node::
PrintPostOrder( ) const
{
	if( this->m_Left != NULL ) this->m_Left->PrintPostOrder( );
	if( this->m_Right != NULL ) this->m_Right->PrintPostOrder( );
	std::cout << this->m_Value << " ";
}

// -------------------------------------------------------------------------
template< class _TValue >
void PUJ::AVLTree< _TValue >::Node::
PrintLevels( ) const
{
	std::queue< Node* > q;
	q.push( this );
	while( !q.empty( ) )
	{
		Node* n = q.front( );
		q.pop( );

		std::cout << n->m_Value << " ";

		if( n->m_Left != NULL )
			q.push( n->m_Left );
		if( n->m_Right != NULL )
			q.push( n->m_Right );

  } // end while
}

// -------------------------------------------------------------------------
template< class _TValue >
std::string PUJ::AVLTree< _TValue >::Node::
PrintAsPNG( ) const
{
	std::stringstream str;
	Node* children[ 2 ];
	children[ 0 ] = this->m_Left;
	children[ 1 ] = this->m_Right;

	for( int i = 0; i < 2; i++ )
	{
		if( children[ i ] != NULL )
		{
			str
			<< ( unsigned long )( this ) << "->"
			<< ( unsigned long )( children[ i ] ) << " "
			<< ( unsigned long )( this )
			<< " [label=" << this->m_Value << "." << this->m_Height << "]; "
			<< ( unsigned long )( children[ i ] )
			<< " [label=" << children[ i ]->m_Value << "."
				<< children[ i ]->m_Height << "]; "
<< children[ i ]->PrintAsPNG( );

    } // fi

  } // rof
  return( str.str( ) );
}

// -------------------------------------------------------------------------
template< class _TValue >
const typename PUJ::AVLTree< _TValue >::Node*
PUJ::AVLTree< _TValue >::Node::
Find( const TValue& v ) const
{
	if( v < this->m_Value )
	{
		if( this->m_Left != NULL )
			return( this->m_Left->Find( v ) );
		else
			return( NULL );
	}
	else if( this->m_Value < v )
	{
		if( this->m_Right != NULL )
			return( this->m_Right->Find( v ) );
		else
			return( NULL );
	}
	else
		return( this );
}

// -------------------------------------------------------------------------
template< class _TValue >
typename PUJ::AVLTree< _TValue >::
Node* PUJ::AVLTree< _TValue >::Node::
RotLeft( Node* x )
{
	Node* y = x->m_Right;
	Node* r = x->m_Left;
	Node* s = y->m_Left;
	Node* t = y->m_Right;

  // Update pointers
	y->m_Left = x;
	x->m_Right = s;

  // Update heights
	long hr = ( r != NULL )? r->m_Height: 0;
	long hs = ( s != NULL )? s->m_Height: 0;
	long ht = ( t != NULL )? t->m_Height: 0;
	x->m_Height = 1 + ( ( hs < hr )? hr: hs );
	y->m_Height = 1 + ( ( ht < x->m_Height )? x->m_Height: ht );

	return( y );
}

// -------------------------------------------------------------------------
template< class _TValue >
typename PUJ::AVLTree< _TValue >::
Node* PUJ::AVLTree< _TValue >::Node::
RotRight( Node* x )
{
	Node* y = x->m_Left;
	Node* r = y->m_Left;
	Node* s = y->m_Right;
	Node* t = x->m_Right;

  // Update pointers
	y->m_Right = x;
	x->m_Left = s;

  // Update heights
	long hr = ( r != NULL )? r->m_Height: 0;
	long hs = ( s != NULL )? s->m_Height: 0;
	long ht = ( t != NULL )? t->m_Height: 0;
	x->m_Height = 1 + ( ( hs < ht )? ht: hs );
	y->m_Height = 1 + ( ( hr < x->m_Height )? x->m_Height: hr );

	return( y );
}

// -------------------------------------------------------------------------
template< class _TValue >
typename PUJ::AVLTree< _TValue >::
Node* PUJ::AVLTree< _TValue >::Node::
RotLeftRight( Node* x )
{
	Node* y = x->m_Right;
	Node* z = y->m_Left;
	Node* r = x->m_Left;
	Node* s = z->m_Left;
	Node* t = z->m_Right;
	Node* u = y->m_Right;

  // Update pointers
	z->m_Left = x;
	z->m_Right = y;
	x->m_Right = s;
	y->m_Left = t;

  // Update heights
	long hr = ( r != NULL )? r->m_Height: 0;
	long hs = ( s != NULL )? s->m_Height: 0;
	long ht = ( t != NULL )? t->m_Height: 0;
	long hu = ( u != NULL )? u->m_Height: 0;
	x->m_Height = 1 + ( ( hs < hr )? hr: hs );
	y->m_Height = 1 + ( ( hu < ht )? ht: hu );
	z->m_Height =
	1 + ( ( y->m_Height < x->m_Height )? x->m_Height: y->m_Height );

	return( z );
}

// -------------------------------------------------------------------------
template< class _TValue >
typename PUJ::AVLTree< _TValue >::
Node* PUJ::AVLTree< _TValue >::Node::
RotRightLeft( Node* x )
{
	Node* y = x->m_Left;
	Node* z = y->m_Right;
	Node* r = y->m_Left;
	Node* s = z->m_Left;
	Node* t = z->m_Right;
	Node* u = x->m_Right;

  // Update pointers
	z->m_Left = y;
	z->m_Right = x;
	x->m_Left = t;
	y->m_Right = s;

  // Update heights
	long hr = ( r != NULL )? r->m_Height: 0;
	long hs = ( s != NULL )? s->m_Height: 0;
	long ht = ( t != NULL )? t->m_Height: 0;
	long hu = ( u != NULL )? u->m_Height: 0;
	x->m_Height = 1 + ( ( hu < ht )? ht: hu );
	y->m_Height = 1 + ( ( hs < hr )? hr: hs );
	z->m_Height =
	1 + ( ( y->m_Height < x->m_Height )? x->m_Height: y->m_Height );

	return( z );
}

// -------------------------------------------------------------------------
template< class _TValue >
PUJ::AVLTree< _TValue >::
AVLTree( )
: m_Root( NULL )
{
}

// -------------------------------------------------------------------------
template< class _TValue >
PUJ::AVLTree< _TValue >::
~AVLTree( )
{
	if( this->m_Root != NULL )
		delete this->m_Root;
}

// -------------------------------------------------------------------------
template< class _TValue >
bool PUJ::AVLTree< _TValue >::
Insert( const TValue& v )
{
	if( this->m_Root == NULL )
	{
		this->m_Root = new Node( v );
		return( true );
	}
	else
	{
		Node* n = this->m_Root->Insert( v );
		if( n != NULL )
		{
			this->m_Root = n;
			return( true );
		}
		else
			return( false );

  } // end if
}

// -------------------------------------------------------------------------
template< class _TValue >
bool PUJ::AVLTree< _TValue >::
Erase( const TValue& v )
{
	if(this->m_Root != NULL)
	{
		Node* ret =  this->m_Root->Erase( v );
		if(ret != NULL)
		{
			this->m_Root = ret;
			return true;
		}
		else return (false);
	}
	else return( false );
}

// -------------------------------------------------------------------------
template< class _TValue >
bool PUJ::AVLTree< _TValue >::
Find( const TValue& v ) const
{
	if( this->m_Root != NULL )
		return( this->m_Root->Find( v ) != NULL );
	else
		return( false );
}

// -------------------------------------------------------------------------
template< class _TValue >
unsigned int PUJ::AVLTree< _TValue >::
Height( ) const
{
	if( this->m_Root != NULL )
		return( this->m_Root->Height( ) );
	else
		return( 0 );
}

// -------------------------------------------------------------------------
template< class _TValue >
unsigned int PUJ::AVLTree< _TValue >::
Weight( ) const
{
	if( this->m_Root != NULL )
		return( this->m_Root->Weight( ) );
	else
		return( 0 );
}

// -------------------------------------------------------------------------
template< class _TValue >
void PUJ::AVLTree< _TValue >::
PrintInOrder( ) const
{
	if( this->m_Root != NULL )
	{
		this->m_Root->PrintInOrder( );
		std::cout << std::endl;

  } // fi
}

// -------------------------------------------------------------------------
template< class _TValue >
void PUJ::AVLTree< _TValue >::
PrintPreOrder( ) const
{
	if( this->m_Root != NULL )
	{
		this->m_Root->PrintPreOrder( );
		std::cout << std::endl;

  } // fi
}

// -------------------------------------------------------------------------
template< class _TValue >
void PUJ::AVLTree< _TValue >::
PrintPostOrder( ) const
{
	if( this->m_Root != NULL )
	{
		this->m_Root->PrintPostOrder( );
		std::cout << std::endl;

  } // fi
}

// -------------------------------------------------------------------------
template< class _TValue >
void PUJ::AVLTree< _TValue >::
PrintLevels( ) const
{
	if( this->m_Root != NULL )
	{
		this->m_Root->PrintLevels( );
		std::cout << std::endl;

  } // fi
}

// -------------------------------------------------------------------------
template< class _TValue >
void PUJ::AVLTree< _TValue >::
PrintAsPNG( const std::string& filename ) const
{
	std::stringstream str;
	str << "echo \"digraph G{";
	if( this->m_Root != NULL )
	{
		if( this->m_Root->IsLeaf( ) )
			str << "\"" << this->m_Root->GetValue( )
		<< "." << this->m_Root->Height( )
		<< "\"";
		else
			str << this->m_Root->PrintAsPNG( );

  } // fi
  str << "}\" | dot -Tpng > " << filename;
  std::system( str.str( ).c_str( ) );
}

#endif // __PUJ__AVLTree__hxx__

// eof - AVLTree.hxx
