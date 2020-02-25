#include <ctime>
#include <cstdio>
#include <iostream>
#include <cstdlib>
#include "OrdBinTree.h"

// -------------------------------------------------------------------------
typedef PUJ::OrdBinTree< unsigned long > TTree;

// -------------------------------------------------------------------------
int main( int argc, char* argv[] )
{
  unsigned long W = std::atol( argv[ 1 ] );
  unsigned long M = std::atol( argv[ 2 ] );

  TTree tree;
  std::srand( std::time( NULL ) );
  while( tree.Weight( ) < W )
  {
    unsigned long v;
    v = ( unsigned long )( std::rand( ) % ( M + 1 ) );
    tree.Insert( v );

  } // elihw
  tree.PrintAsPNG( "tree.png" );
  return( 0 );
}

// eof - test_OrdBinTree_01.cxx
