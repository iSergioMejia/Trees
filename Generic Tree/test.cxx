/*┌───────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────┐ 
**│Code made by Leonardo Florez Valencia                                                                                          │
**│                                                                                                                               │
**│Modified and completed by Sergio Mejía, Laura Jiménez and Sebastián Gutierrez                                                  │
**│for the Data Structures lesson 1830                                                                                            │
**│                                                                                                                               │
**│All the methods of the Generic Tree are implemented completely. However, due to some unknown                                   │
**│errors with the TTreeList, the methods AreIsomorphic and IsContained cannot be tested.                                         │
**│                                                                                                                               │
**│Also, the commented section after the main for statemente can be used to check some of the Generic Tree methods. However in the│
**│current status of the main function (with the tree list declaration inside the for statement) this code section will not work. │
**└───────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────┘ 
*/

#include <cstdlib>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

#include "GenericTree.h"

// -------------------------------------------------------------------------
typedef int TData;
typedef PUJ::GenericTree< TData > TTree;
typedef std::vector< TTree > TTreeList;

// -------------------------------------------------------------------------
int main( int argc, char* argv[] )
{
  if( argc < 2 )
  {
    std::cerr << "Usage: " << argv[ 0 ] << " input_tree" << std::endl;
    return( 1 );

  } // fi
  std::string input_tree_filename = argv[ 1 ];

  // Read file into a buffer
  std::ifstream input_tree_file(
    input_tree_filename.c_str( ),
    std::ios::in | std::ios::binary | std::ios::ate
    );

  if( !( input_tree_file.is_open( ) ) )
  {
    std::cerr
      << "Unable to open file \"" << input_tree_filename << "\""
      << std::endl;
    return( 1 );

  } // fi
  std::streampos size = input_tree_file.tellg( );
  char* buffer = new char [ size ];
  input_tree_file.seekg( 0, std::ios::beg );
  input_tree_file.read( buffer, size );
  input_tree_file.close( );

  // Put buffer into a string stream
  std::stringstream input_tree_stream( buffer, std::ios_base::in );

  // Read trees
  
  unsigned int nTrees = 0;
  input_tree_stream >> nTrees;
  //std::cout << nTrees;
  for( unsigned int tId = 0; tId < nTrees; ++tId )
  {
    TTreeList tree_list;

    tree_list.push_back( TTree( ) );
    tree_list.rbegin( )->BuildFromPreorder( input_tree_stream );
    
    std::string pngFile = "test";
    pngFile += std::to_string((int)tId);
    pngFile += ".png";

    std::cout << "Weight:       " << tree_list.rbegin( )->Weight() << std::endl;
    std::cout << "Height:       " << tree_list.rbegin( )->Height() << std::endl;
    std::cout << "Global Order: " << tree_list.rbegin( )->GlobalOrder() << std::endl;
    std::cout << "Width:        " << tree_list.rbegin( )->Width() << std::endl;

    std::cout << std::endl;
    std::cout << "PreOrder: ";
    tree_list.rbegin( )->PrintPreOrder();
    std::cout << std::endl;
    std::cout << "PosOrder: ";
    tree_list.rbegin( )->PrintPostOrder();
    std::cout << std::endl;
    std::cout << "InOrder:  ";
    tree_list.rbegin( )->PrintInOrder();
    std::cout << std::endl;
    std::cout << "Levels:   ";
    tree_list.rbegin( )->PrintLevels();
    std::cout << std::endl;

    unsigned int height = tree_list.rbegin()->Height();

    for(unsigned int j = 1; j <= height; j++)
    {
      std::cout << "(L->R) Nodes in level " << j << ": ";
      tree_list.rbegin()->LevelValues(j,true);
      std::cout << std::endl;

      std::cout << "(R->L) Nodes in level " << j << ": ";
      tree_list.rbegin()->LevelValues(j,false);
      std::cout << std::endl;
    }

    std::cout << std::endl;
    
    std::cout << "Is AVL?: " << ((tree_list.rbegin()->IsAVL())? "Yes\n" : "No\n");
    std::cout << "Is Heap?: " << ((tree_list.rbegin()->IsHeap())? "Yes\n" : "No\n");

    tree_list.rbegin()->PrintAsPNG(pngFile);

  } // rof

  /*┌───────────────────────────────────────────────────────────────────────────────────────────────────────────────────┐
  **│This code section can be used to test some methods. However, in the current status of the main, it will not work.  │
  **│Some methods calls can be moved to the for statement to use it like the other ones, although they were intented to │
  **│use it with a certain tree (in_mine.txt, with the tree of -4900 as root)                                           │
  **└───────────────────────────────────────────────────────────────────────────────────────────────────────────────────┘
  */
  /*
  int a = -2001;
  int b = -1202;
  int c = -1;
  std::vector<int> resultado;

  std::cout << "Common Ancestor between " << a << " and " << b << ": ";
  const int* result = tree_list.rbegin( )->CommonAncestor(a,b);
  if(result != NULL) std::cout << *result;
  else std::cout << "Uno de los valores no existe";
  std::cout << std::endl;

  std::cout << "Road between " << a << " and " << b << ": ";
  resultado = tree_list.rbegin( )->PathBetweenTwoNodes(a,b);
  if(resultado.size() > 0)
    for (std::vector<int>::iterator it = resultado.begin(); it != resultado.end(); it++)
    {
      std::cout << *it << "->";
    }
  else std::cout << "Uno de los valores no existe";
  std::cout << std::endl;

  std::cout << c << " is: " << tree_list.rbegin()->countRepeated(c) << " times.\n";

  std::cout << "The repeated values in the tree are: ";
  resultado = tree_list.rbegin()->getRepeatedValues();
  for (std::vector<int>::iterator it = resultado.begin(); it != resultado.end(); it++)
  {
    std::cout << *it << ", ";
  }
  std::cout << std::endl;

  std::cout << "\nEnd\n";*/

  // Free buffer
  delete[] buffer;

  // TODO

  return( 0 );
}

// eof - test.cxx
