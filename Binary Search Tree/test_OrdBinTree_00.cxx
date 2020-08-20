#include <iostream>
#include <sstream>

#include "OrdBinTree.h"

// -------------------------------------------------------------------------
typedef PUJ::OrdBinTree< int > TTree;

// -------------------------------------------------------------------------
int main( int argc, char* argv[] )
{
  TTree tree;

  unsigned int count = 0;
  while( 1 )
  {
    char op;
    int v;
    std::cin >> op >> v;

    if( op == 'a' )
      tree.Insert( v );

    std::stringstream ss;
    ss << "bin_tree_" << count++ << ".png";
    tree.PrintAsPNG( ss.str( ) );

  } // elihw

  return( 0 );
}

// eof - test_OrdBinTree_00.cxx
