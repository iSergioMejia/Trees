/*┌──────────────────────────────────────────────────────────────────────────────┐
**│Code made by Leonardo Florez Valencia																				 │
**│ 																																						 │
**│Modified and completed by Sergio Mejía, Laura Jiménez and Sebastián Gutierrez │
**│for the Data Structures lesson 1830																					 │
**└──────────────────────────────────────────────────────────────────────────────┘
*/

#ifndef __GENERICTREE__HXX__
#define __GENERICTREE__HXX__

#include <cstdlib>
#include <iostream>
#include <sstream>
#include <queue>
#include <cmath>
#include <algorithm>
#include <map>

// -------------------------------------------------------------------------
template< class T >
PUJ::GenericTree< T >::Node::
Node( )
{
}

// -------------------------------------------------------------------------
template< class T >
PUJ::GenericTree< T >::Node::
~Node( )
{
  typename TChildren::iterator cIt = this->m_Children.begin( );
  for( ; cIt != this->m_Children.end( ); cIt++ )
  {
    delete *cIt;
  }
  this->m_Children.clear();
}

// -------------------------------------------------------------------------
template< class T >
void PUJ::GenericTree< T >::Node::
BuildFromPreorder( std::istream& input )
{
  T value;
  unsigned int nChild;
  input >> nChild;
  input >> value;
  this->SetValue( value );
  this->m_Children.clear();

  for(unsigned int i = 0; i < nChild; i++)
  {
    Node* newChild = new Node( );
    newChild->BuildFromPreorder( input );
    this->m_Children.push_back(newChild);
  }
}

// -------------------------------------------------------------------------
template< class T >
const T& PUJ::GenericTree< T >::Node::
GetValue( ) const
{
  return( this->m_Value );
}

// -------------------------------------------------------------------------
template< class T >
void PUJ::GenericTree< T >::Node::
SetValue( const T& v )
{
  this->m_Value = v;
}

// -------------------------------------------------------------------------
template< class T >
void PUJ::GenericTree< T >::Node::
AddChild( const T& v )
{
  Node* n = new Node( );
  n->m_Value = v;
  this->m_Children.push_back( n );
}

// -------------------------------------------------------------------------
template< class T >
bool PUJ::GenericTree< T >::Node::
IsLeaf( ) const
{
  if(this->m_Children.empty())
    return true;
  return false;
}

// -------------------------------------------------------------------------
template< class T >
unsigned int PUJ::GenericTree< T >::Node::
Height( ) const
{
  unsigned int curHeight, maxHeight;
  curHeight = maxHeight = 0;
  typename TChildren::const_iterator itC = this->m_Children.cbegin();
  for(; itC != this->m_Children.cend(); itC++)
  {
    curHeight = (*itC)->Height();
    if(curHeight > maxHeight)
      maxHeight = curHeight;
  }
  return(1 + maxHeight);
}

// -------------------------------------------------------------------------
template< class T >
unsigned int PUJ::GenericTree< T >::Node::
Weight( ) const
{
  unsigned int childWeight, treeWeight;
  childWeight = treeWeight = 0;
  typename TChildren::const_iterator itC = this->m_Children.cbegin();
  for(; itC != this->m_Children.cend(); itC++)
  {
    childWeight = (*itC)->Weight();
    treeWeight += childWeight;
  }
  return (1 + treeWeight);
}

// -------------------------------------------------------------------------
template< class T >
unsigned int PUJ::GenericTree< T >::Node::
GlobalOrder( ) const
{
  unsigned int biggest = this->m_Children.size();
  typename TChildren::const_iterator itC = this->m_Children.cbegin();
  for(; itC != this->m_Children.cend(); itC++)
  {
    int childBiggest = (*itC)->GlobalOrder();
    if(childBiggest > biggest)
      biggest = childBiggest;
  }
  return (biggest);
}

// -------------------------------------------------------------------------
template< class T >
unsigned int PUJ::GenericTree< T >::Node::
Width( )
{
  typedef PUJ::GenericTree< T >::Node Nodo;
  std::queue <Nodo*> auxQueue;
  auxQueue.push(this);
  int maxWidth = 0;
  while( !auxQueue.empty() )
  {
    int width = auxQueue.size();

    if(width > maxWidth)
      maxWidth = width;

    while(width--)
    {
      Nodo* nodoActual = auxQueue.front(); auxQueue.pop();
      typename TChildren::iterator itC = nodoActual->m_Children.begin();
      for(; itC != nodoActual->m_Children.end();itC++)
       auxQueue.push((*itC));
    }
  }
  return maxWidth;
}

// -------------------------------------------------------------------------
template< class T >
void PUJ::GenericTree< T >::Node::
PrintInOrder( ) const
{
  typename TChildren::const_iterator itC = this->m_Children.cbegin();
  bool hasChild = false;
  if(itC != this->m_Children.end())
  {
    hasChild = true;
    (*itC)->PrintInOrder();
    itC++;
  }
  std::cout << this->m_Value << ", ";
  if(hasChild)
    for(; itC != this->m_Children.cend();itC++)
        (*itC)->PrintInOrder();
}

// -------------------------------------------------------------------------
template< class T >
std::vector<int> PUJ::GenericTree< T >::Node::
GetInOrder( ) const
{
  std::vector<int> ret;

  typename TChildren::const_iterator itC = this->m_Children.cbegin();
  bool hasChild = false;
  if(itC != this->m_Children.end())
  {
    hasChild = true;
    ret = (*itC)->GetInOrder();
    itC++;
  }

  ret.push_back(this->m_Value);

  if(hasChild)
    for(; itC != this->m_Children.cend();itC++)
    {
      std::vector<int> res = (*itC)->GetInOrder();
      ret.insert(ret.end(), res.begin(), res.end());
    }
  return(ret);
}


// -------------------------------------------------------------------------
template< class T >
void PUJ::GenericTree< T >::Node::
PrintPreOrder( ) const
{
  std::cout << this->m_Value << ", ";
  typename TChildren::const_iterator itC = this->m_Children.cbegin();
  for(; itC != this->m_Children.end();itC++)
      (*itC)->PrintPreOrder();
}

// -------------------------------------------------------------------------
template< class T >
void PUJ::GenericTree< T >::Node::
PrintPostOrder( ) const
{
  typename TChildren::const_iterator itC = this->m_Children.cbegin();
  for(; itC != this->m_Children.cend();itC++)
      (*itC)->PrintPostOrder();
  std::cout << this->m_Value << ", ";

}

// -------------------------------------------------------------------------
template< class T >
void PUJ::GenericTree< T >::Node::
PrintLevels( )
{
  typedef PUJ::GenericTree< T >::Node Nodo;
  std::queue <Nodo*> auxQueue;
  auxQueue.push(this);
  while( !auxQueue.empty() )
  {
    const Nodo* nodoActual = auxQueue.front(); auxQueue.pop();
    std::cout << nodoActual->m_Value << ", ";
    typename TChildren::const_iterator itC = nodoActual->m_Children.cbegin();
    for(; itC != nodoActual->m_Children.cend();itC++)
      auxQueue.push((*itC));
  }
}

// -------------------------------------------------------------------------
template< class T >
std::string PUJ::GenericTree< T >::Node::
PrintAsPNG( ) const
{
  std::stringstream str;

  if( !this->IsLeaf( ) )
  {
    for(
      typename TChildren::const_iterator cIt = this->m_Children.begin( );
      cIt != this->m_Children.end( );
      ++cIt
      )
    {
      str << (unsigned long)this << "->" << (unsigned long)(*cIt) << " ";
      str << (unsigned long)this << " [label=\"" << this->m_Value << "\"]; ";
      str << (unsigned long)( *cIt ) << " [label=\"" << ( *cIt )->GetValue( )  << "\"]; ";
      str << ( *cIt )->PrintAsPNG( );

    } // rof
  }
  else
    str << (unsigned long)this << " [label=\"" << this->m_Value << "\"]; ";
  return( str.str( ) );
}

// -------------------------------------------------------------------------
template< class T >
typename PUJ::GenericTree< T >::Node*
PUJ::GenericTree< T >::Node::
Find( const T& v )
{
  Node* ret = NULL;
  if(this->m_Value == v)
    return this;

  typename TChildren::const_iterator itC = this->m_Children.cbegin();
  for(; itC != this->m_Children.cend();itC++)
  {
    Node* res = (*itC)->Find( v );
    if(res != NULL)
      ret = res;
  }
  return ( ret );
}

// -------------------------------------------------------------------------
template< class T >
const typename PUJ::GenericTree< T >::Node*
PUJ::GenericTree< T >::Node::
Find( const T& v ) const
{
  Node* ret = NULL;
  if(this->m_Value == v)
    return this;

  typename TChildren::const_iterator itC = this->m_Children.cbegin();
  for(; itC != this->m_Children.cend();itC++)
  {
    Node* res = (*itC)->Find( v );
    if(res != NULL)
      ret = res;
  }
  return ( ret );
}

// -------------------------------------------------------------------------
template< class T >
typename PUJ::GenericTree< T >::Node* const
PUJ::GenericTree< T >::Node::
CommonAncestor(const T& v1, const T& v2)
{
  if(v1==this->m_Value || v2==this->m_Value)
  {
    return this;
  }

  int count = 0;
  Node* temp = NULL;

  typename TChildren::const_iterator itC = this->m_Children.cbegin();
  for(; itC != this->m_Children.cend();itC++)
  {
     Node* const common = (*itC)->CommonAncestor(v1,v2);
     if(common != NULL)
     {
      temp = common;
      count++;
     }
  }
  if(count == 2)
  {
    return this;
  }

  return temp;
}

// -------------------------------------------------------------------------
template< class T >
const std::vector < int > PUJ::GenericTree< T >::Node::
FindPath( const T& v )
{
  std::vector <int> ret;

  if(this->m_Value == v)
  {
    ret.push_back(this->m_Value);
    return(ret);
  }

  typename TChildren::iterator itC = this->m_Children.begin();
  for(; itC != this->m_Children.end();itC++)
  {
    std::vector <int> res = (*itC)->FindPath( v );
    if(!res.empty())
    {
      ret = res;
      ret.push_back(this->m_Value);
    }
  }

  return( ret );

}

// -------------------------------------------------------------------------
template< class T >
std::vector < int > PUJ::GenericTree< T >::Node::
PathBetweenTwoNodes(const T& v1, const T& v2) //const
{
  Node* const lca = this->CommonAncestor(v1,v2);

  std::vector <int> ret1 = lca->FindPath(v1);
  std::vector <int> ret2 = lca->FindPath(v2);

  std::vector<int> res;

  if(!ret1.empty())
  {
    res = ret2;
    if(ret1.rbegin()+1 != ret1.rend())
      res.insert(res.end(), ret1.rbegin()+1, ret1.rend());
    else
      res.insert(res.end(), ret1.rbegin(), ret1.rend());
  }
  else if(!ret2.empty())
  {
    res = ret1;
    if(ret2.rbegin()+1 != ret2.rend())
      res.insert(res.end(), ret2.rbegin()+1, ret2.rend());
    else
      res.insert(res.end(), ret2.rbegin(), ret2.rend());
  }

  return (res);
}

// -------------------------------------------------------------------------
template< class T >
std::vector < const typename PUJ::GenericTree< T >::Node* > PUJ::GenericTree< T >::Node::
LevelValues(unsigned int level, unsigned int thisLevel) const
{
  std::vector<const Node*> ret;
  if(level == thisLevel)
  {
    ret.push_back(this);
    return (ret);
  }

  typename TChildren::const_iterator itC = this->m_Children.begin();
  for(; itC != this->m_Children.end();itC++)
  {
    std::vector<const Node*> res = (*itC)->LevelValues(level, thisLevel+1);
    ret.insert(ret.end(), res.begin(), res.end());
  }

  return (ret);
}

//---------------------------------------------------------------------------
template< class T >
unsigned int PUJ::GenericTree< T >::Node::
countRepeated(const T& v) const
{
  if(v == this->m_Value)
    return (1);

  unsigned int repeated = 0;
  typename TChildren::const_iterator itC = this->m_Children.cbegin();
  for(; itC != this->m_Children.cend();itC++)
  {
    repeated += (*itC)->countRepeated(v);
  }

  return (repeated);

}

// -------------------------------------------------------------------------
template< class T >
bool PUJ::GenericTree< T >::Node::
IsAVL()
{

  typename TChildren::const_iterator itC = this->m_Children.cbegin();

  long b = ( this->m_Children.size() > 0 )? (*itC)->Height() : 0;

  itC++;
  b     -= ( this->m_Children.size() ==2 )? (*itC)->Height() : 0;

  if( abs(b) > 1)
    return false;


  itC = this->m_Children.cbegin();
  bool left = ( this->m_Children.size() > 0 )? (*itC)->IsAVL() : 1;
  itC++;
  bool right = ( this->m_Children.size() ==2 )? (*itC)->IsAVL() : 1;
  if(left && right)
    return true;
  else return false;

}

// -------------------------------------------------------------------------
template< class T >
bool PUJ::GenericTree< T >::Node::
IsHeap()
{
  bool isHeap = true;
  typename TChildren::const_iterator itC = this->m_Children.cbegin();
  for(; itC != this->m_Children.cend();itC++)
  {
    if( (*itC)->m_Value > this->m_Value)
    {
      isHeap = false;
    }
    else
    {
      isHeap = true;
      isHeap = (*itC)->IsHeap();
    }
  }
  return (isHeap);
}

//--------------------------------------------------------------------------
template< class T >
bool PUJ::GenericTree< T >::Node::
IsSemiComplete( ) const
{
  int height = this->Height();
  bool isSemiComplete = true;
  for(int i = 1; i <= height; i++)
  {
    std::vector <const Node*> levelValues = (this->LevelValues(i,1));
    if(i != height)
      if( levelValues.size() != ( pow( 2, (i-1) ) ) )
        isSemiComplete = false;
    if((i+1) == height)
    {
      bool twoChilds = true;
      typename std::vector <const Node*>::iterator itLV = levelValues.begin();
      for( ; itLV != levelValues.end(); itLV++)
      {
        if(twoChilds == true)
        {
          if((*itLV)->m_Children.size() < 2)
          {
            twoChilds = false;
          }
        }
        else if((*itLV)->m_Children.size() > 0)
        {
          isSemiComplete = false;
        }
      }
    }
  }

  return isSemiComplete;

}

// -------------------------------------------------------------------------
template< class T >
bool PUJ::GenericTree< T >::Node::
AreIsomorphic(const Node* otherTree) const
{
	if(this->m_Children == otherTree->m_Children)
	{
		typename TChildren::const_iterator itC = this->m_Children.cbegin();
		typename TChildren::const_iterator itCO = otherTree->m_Children.cbegin();

		bool areIso = true;

  	for( ; itC != this->m_Children.cend() && itCO != otherTree->m_Children.cend();itCO++, itC++)
  	{
  		areIso = (areIso && (*itC)->AreIsomorphic((*itCO)));
		}
		return ( areIso );
	}
	return ( false );
}

// -------------------------------------------------------------------------
template< class T >
bool PUJ::GenericTree< T >::Node::
IsContained(const Node* otherTree) const
{
	if(this->m_Children == otherTree->m_Children)
	{
		typename TChildren::const_iterator itC = this->m_Children.cbegin();
		typename TChildren::const_iterator itCO = otherTree->m_Children.cbegin();

		bool isCon = true;

  	for( ; itC != this->m_Children.cend() && itCO != otherTree->m_Children.cend();itCO++, itC++)
  	{
  		if((*itC)->GetValue() != (*itCO)->GetValue())
  			return ( false );
  		isCon = (isCon && (*itC)->IsContained((*itCO)));
		}
		return ( isCon );
	}
	return ( false );
}

//--------------------------------------------------------------------------
//TREE METHODS
// -------------------------------------------------------------------------
template< class T >
PUJ::GenericTree< T >::
GenericTree( )
  : m_Root( NULL )
{
}

// -------------------------------------------------------------------------
template< class T >
PUJ::GenericTree< T >::
~GenericTree( )
{
  if( this->m_Root != NULL )
  {
    delete this->m_Root;
  }
}

// -------------------------------------------------------------------------
template< class T >
void PUJ::GenericTree< T >::
BuildFromPreorder( std::istream& input )
{
  if( this->m_Root != NULL)
    delete this->m_Root;
  this->m_Root = new Node();
  this->m_Root->BuildFromPreorder( input );
}

// -------------------------------------------------------------------------
template< class T >
bool PUJ::GenericTree< T >::
Find( const T& v ) const
{
  if( this->m_Root != NULL )
    return( this->m_Root->Find( v ) != NULL );
  else
    return( false );
}

// -------------------------------------------------------------------------
template< class T >
const typename PUJ::GenericTree< T >::TValue*
PUJ::GenericTree< T >::
CommonAncestor(const T& v1, const T& v2) const
{
  if( this->m_Root != NULL )
  {
    bool r1 = this->Find( v1 );
    bool r2 = this->Find( v2 );
    if(r1 && r2)
    {
      const Node* ret = this->m_Root->CommonAncestor( v1, v2);
      return( &(ret->GetValue()) );
    }
  }
  else
    return( NULL );
}

// -------------------------------------------------------------------------
template< class T >
std::vector<int> PUJ::GenericTree< T >::
PathBetweenTwoNodes(const T& v1, const T& v2) const
{
  std::vector <int> ret;
  if(this->m_Root != NULL)
  {
    bool r1 = this->Find( v1 );
    bool r2 = this->Find( v2 );
    if(r1 && r2)
    {
      ret = this->m_Root->PathBetweenTwoNodes(v1,v2);
    }
  }
  return ( ret );
}

// -------------------------------------------------------------------------
template< class T >
void PUJ::GenericTree< T >::
LevelValues(unsigned int level, bool LROrder)
{
  if(this->m_Root != NULL)
  {
    if(level > 0 && level <= this->m_Root->Height())
    {
      std::vector<const Node*> ret = this->m_Root->LevelValues( level, 1);

      if(LROrder)
      {
        for(int i = 0; i < ret.size(); i++)
        {
          std::cout << ret[i]->GetValue() << ", ";
        }
      }
      else
      {
        for(int i = ret.size()-1; i >= 0; i--)
        {
          std::cout << ret[i]->GetValue() << ", ";
        }
      }
    }
    else std::cout << "Level out of tree range\n";
  }
}

template< class T >
unsigned int PUJ::GenericTree< T >::
countRepeated(const T& v) const
{
  if(this->m_Root != NULL)
  {
    return ( this->m_Root->countRepeated( v ) );
  }
  else return ( 0 );
}

template < class T >
std::vector <int> PUJ::GenericTree< T >::
getRepeatedValues()
{
  std::vector<int> repeated;
  if(this->m_Root != NULL)
  {
    std::vector <int> treeValues = this->m_Root->GetInOrder();

    for(std::vector<int>::iterator it = treeValues.begin(); it != treeValues.end() ; it++)
    {
      int nR = this->countRepeated(*it);
      if(nR > 1)
      {
        bool mou = false;
        for(std::vector<int>::iterator itR = repeated.begin(); itR != repeated.end() ; itR++)
          if(*it == *itR ) mou = true;
        if(!mou)
          repeated.push_back(*it);
      }
    }
  }
  return ( repeated );
}

// -------------------------------------------------------------------------
template< class T >
bool PUJ::GenericTree< T >::
IsAVL()
{
  if(this->m_Root != NULL)
  {
    if(this->m_Root->GlobalOrder() <= 2 )
    {
      std::vector<int> inorder = this->m_Root->GetInOrder();
      bool isSorted = std::is_sorted(inorder.begin(), inorder.end());

      if(isSorted)
        if(this->m_Root->IsAVL())
          return (true);
    }
  }

  return (false);
}

// -------------------------------------------------------------------------
template< class T >
bool PUJ::GenericTree< T >::
IsHeap()
{
  if(this->m_Root != NULL)
  {
    if(this->m_Root->GlobalOrder() <= 2 )
    {
      int height = this->m_Root->Height();
      bool isSemi = this->m_Root->IsSemiComplete();
      if(isSemi)
      {
        if(this->m_Root->IsHeap())
        {
          return (true);
        }
      }
    }
  }

  return false;

}

// -------------------------------------------------------------------------
template< class T >
bool PUJ::GenericTree< T >::
AreIsomorphic(const GenericTree<T>& otherTree) const
{
	if(this->m_Root != NULL && otherTree.m_Root != NULL)
	{
		this->m_Root->AreIsomorphic(otherTree.m_Root);
	}
}

// -------------------------------------------------------------------------
template< class T >
bool PUJ::GenericTree< T >::Node::
IsContained(const GenericTree<T>& otherTree) const
{
	if(this->m_Root != NULL && otherTree.m_Root != NULL)
	{
		Node* ret = this->m_Root->Find(otherTree.m_Root->m_Value);
		if(ret != NULL)
			return (this->m_Root->IsContained(otherTree.m_Root));
		else return false;
	}
	else return false;
}

// -------------------------------------------------------------------------
template< class T >
unsigned int PUJ::GenericTree< T >::
Height( ) const
{
  if( this->m_Root != NULL )
    return( this->m_Root->Height( ) );
  else
    return( 0 );
}

// -------------------------------------------------------------------------
template< class T >
unsigned int PUJ::GenericTree< T >::
Weight( ) const
{
  if( this->m_Root != NULL )
    return( this->m_Root->Weight( ) );
  else
    return( 0 );
}

// -------------------------------------------------------------------------
template< class T >
unsigned int PUJ::GenericTree< T >::
GlobalOrder( ) const
{
  if( this->m_Root != NULL )
    return( this->m_Root->GlobalOrder( ) );
  else
    return( 0 );
}

// -------------------------------------------------------------------------
template< class T >
unsigned int PUJ::GenericTree< T >::
Width( ) const
{
  if( this->m_Root != NULL )
    return( this->m_Root->Width( ) );
  else
    return( 0 );
}

// -------------------------------------------------------------------------
template< class T >
void PUJ::GenericTree< T >::
PrintInOrder( ) const
{
  if( this->m_Root != NULL )
    this->m_Root->PrintInOrder( );
}

// -------------------------------------------------------------------------
template< class T >
void PUJ::GenericTree< T >::
PrintPreOrder( ) const
{
  if( this->m_Root != NULL )
    this->m_Root->PrintPreOrder( );
}

// -------------------------------------------------------------------------
template< class T >
void PUJ::GenericTree< T >::
PrintPostOrder( ) const
{
  if( this->m_Root != NULL )
    this->m_Root->PrintPostOrder( );
}

// -------------------------------------------------------------------------
template< class T >
void PUJ::GenericTree< T >::
PrintLevels( ) const
{
  if( this->m_Root != NULL )
    this->m_Root->PrintLevels( );
}

// -------------------------------------------------------------------------
template< class T >
void PUJ::GenericTree< T >::
PrintAsPNG( const std::string& filename ) const
{
  std::stringstream str;
  str << "echo \"digraph G{";
  if( this->m_Root != NULL )
    str << this->m_Root->PrintAsPNG( );
  str << "}\" | dot -Tpng > " << filename;
  std::system( str.str( ).c_str( ) );
}

#endif // __GENERICTREE__HXX__

// eof - GenericTree.hxx
