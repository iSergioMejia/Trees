#include "kDTree.h"
#include "kDPoint.h"
#include <iostream>
#include <vector>
#include <algorithm>
#include <sstream>

template <class _TValue >
PUJ::kDTree<_TValue>::
kDTree()
{
	
}

template <class _TValue >
PUJ::kDTree<_TValue>::
kDTree(std::vector<TValue>& v)
{
	this->m_Root = new Node(v, 0, (unsigned int)(v.size()-1), 0);
}

template <class _TValue >
PUJ::kDTree<_TValue>::
~kDTree()
{
	delete m_Root;
}

template <class _TValue>
PUJ::kDTree<_TValue>::Node::
Node()
{
	this->m_Right = NULL;
	this->m_Left = NULL;
}

template <class _TValue>
PUJ::kDTree<_TValue>::Node::
~Node()
{
	if(m_Left != NULL) delete m_Left;
	if(m_Right != NULL) delete m_Right;
}

template <class _TValue>
PUJ::kDTree<_TValue>::Node::
Node(std::vector<TValue>& v, unsigned int pI, unsigned int pF, unsigned int crit)
{
	this->m_Right = NULL;
	this->m_Left = NULL;
	if(pI < pF)
	{
		if(crit == 0) std::sort(v.begin()+pI, v.begin()+pF+1, PUJ::orderbyX);
		else if(crit == 1) std::sort(v.begin()+pI, v.begin()+pF+1, PUJ::orderbyY);
		else std::sort(v.begin()+pI, v.begin()+pF+1, PUJ::orderbyZ);
		
		crit = (crit+1)%3;

		// for(int i = pI; i<=pF; i++)
		// 	std::cout << v[i].getX() << " " << v[i].getY() << " " << v[i].getZ() << std::endl;
		// std::cout << std::endl;

		int mediana = (pI+pF)/2;
		
		this->m_Value = v[mediana];
		
		// std::cout << "pI: " << pI << " pF: " << pF << std::endl;
		// std::cout << "this Node: " << v[mediana].getX() << " " << v[mediana].getY() << " " << v[mediana].getZ() << std::endl;
		// std::cout << "Me: " << mediana << std::endl;

		if((int)pI <= (mediana-1) && this->m_Left == NULL)
		{
			//std::cout << "Let's go left!\n";
			this->m_Left = new Node(v,pI,mediana-1, crit);

		}
		if((mediana+1) <= (int)pF && this->m_Right == NULL)
		{
			//std::cout << "Let's go right!\n";
			this->m_Right = new Node(v,mediana+1,pF, crit);	
		}
	}
	else
	{
		if(pI==pF)
		{
			this->m_Value = v[pI];
		}
	}
			

}

template< class _TValue >
std::string PUJ::kDTree< _TValue >::Node::
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
			<< " [label=" << this->m_Value.getX() << this->m_Value.getY() << this->m_Value.getZ()  << "]; "
			<< ( unsigned long )( children[ i ] )
			<< " [label=" << children[ i ]->m_Value.getX() << children[ i ]->m_Value.getY() << children[ i ]->m_Value.getZ()  << "]; "
			<< children[ i ]->PrintAsPNG( );

    } // fi

  } // rof
  return( str.str( ) );
}

template< class _TValue >
void PUJ::kDTree< _TValue >::
PrintAsPNG( const std::string& filename ) const
{
	std::stringstream str;
	str << "echo \"digraph G{";
	if( this->m_Root != NULL )
	{
		if( this->m_Root->m_Right == NULL && this->m_Root->m_Left == NULL  )
			str << "\"" << this->m_Root->m_Value.getX() << this->m_Root->m_Value.getY() << this->m_Root->m_Value.getZ() << "\"";
		else
			str << this->m_Root->PrintAsPNG( );

  } // fi
  str << "}\" | dot -Tpng > " << filename;
  std::system( str.str( ).c_str( ) );
  //std::cout << str.str( ) << std::endl;
}

template< class _TValue >
void PUJ::kDTree< _TValue >::
PrintPreOrder()
{
	if(this->m_Root != NULL)
		m_Root->PrintPreOrder();
}

template< class _TValue >
void PUJ::kDTree< _TValue >::Node::
PrintPreOrder()
{
	std::cout << "Node: ";
	std::cout << this->m_Value.getX() << "/" << this->m_Value.getY() << "/" << this->m_Value.getZ() << std::endl;
	if(this->m_Left != NULL)
	{
		//std::cout << "I'm left: ";
		this->m_Left->PrintPreOrder();
	}
	if(this->m_Right != NULL)
	{
		//std::cout << "I'm right: ";
		this->m_Right->PrintPreOrder();
	}
}

template< class _TValue >
const typename PUJ::kDTree< _TValue >::TValue* PUJ::kDTree< _TValue >::
Find(const TValue& v) const
{
	if(this->m_Root != NULL)
	{
		double distance = PUJ::Distance(v,this->m_Root->m_Value);
		const Node* ret = this->m_Root->Find( v, 0, distance );
		if(ret!=NULL)
			return(&(ret->m_Value));
		else return( &(this->m_Root->m_Value) );
	}
	else return NULL;
}


template< class _TValue >
const typename PUJ::kDTree< _TValue >::Node* 
PUJ::kDTree< _TValue >::Node::
Find(const TValue& v, unsigned int crit, double& min_distance) const
{
	if(this->m_Right == NULL && this->m_Left == NULL)
	{
		double this_distance = Distance(this->m_Value, v);
		if(this_distance < min_distance)
		{
			min_distance = this_distance;
			return this;
		}
		return NULL;
	}
	else
	{
		const Node* ret = NULL;
		crit = (crit+1)%3;
		if(this->m_Value.getValue(crit) < v.getValue(crit))
		{
		 	if(this->m_Right != NULL) 
			{
				ret = this->m_Right->Find(v,crit, min_distance);
			}
			double this_distance = Distance(this->m_Value, v);
			if(this_distance < min_distance)
			{
				min_distance = this_distance;
				ret = this;
			}
			if(abs(v.getValue(crit)-this->m_Value.getValue(crit)) < min_distance)
			{
				const Node* ret2 = NULL;
				if(this->m_Left != NULL) ret2 = this->m_Left->Find(v,crit,min_distance);
				if(ret2 != NULL) ret = ret2;
			}
			return ret;
		}
		else if(v.getValue(crit) < this->m_Value.getValue(crit))
		{
			if(this->m_Left != NULL) 
			{
				ret = this->m_Left->Find(v,crit, min_distance);
			}
			double this_distance = Distance(this->m_Value, v);
			if(this_distance < min_distance)
			{
				min_distance = this_distance;
				ret = this;
			}
				if(abs(v.getValue(crit)-this->m_Value.getValue(crit)) < min_distance)
			{
				const Node* ret2 = NULL;
				if(this->m_Right != NULL) ret2 = this->m_Right->Find(v,crit,min_distance);
				if(ret2 != NULL) ret = ret2;
			}
			return ret;
		}
		else
		{
			double this_distance = Distance(this->m_Value, v);
			if(this_distance < min_distance)
			{
				min_distance = this_distance;
				ret = this;
			}
			if(abs(v.getValue(crit)-this->m_Value.getValue(crit)) < min_distance)
			{
				const Node* ret2 = NULL;
				if(this->m_Right != NULL) ret2 = this->m_Right->Find(v,crit,min_distance);
				if(ret2 != NULL) ret = ret2;
				if(this->m_Left != NULL) ret2 = this->m_Left->Find(v,crit,min_distance);
				if(ret2 != NULL) ret = ret2;
			}
			return ret;
		}
	}
}
