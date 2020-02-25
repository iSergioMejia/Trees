#ifndef __PUJ__kDTree__h__
#define __PUJ__kDTree__h__

#include <vector>

namespace PUJ
{
	template < class _TValue >
	class kDTree
	{
	public:
		typedef _TValue TValue;
		typedef kDTree Self;

	protected:
		class Node
		{
		public:
			Node();
			virtual ~Node();
			Node(std::vector<TValue>& v, unsigned int pI, unsigned int pF, unsigned int crit);

			Node* Insert( const TValue& v );
			const Node* Find(const TValue& v, unsigned int crit, double& min_distance) const;
			std::string PrintAsPNG( ) const;
			void PrintPreOrder();

		public:
			TValue m_Value;
			Node* m_Left;
			Node* m_Right;
		};
	public:

		kDTree();
		kDTree( std::vector<TValue>& v );
		virtual ~kDTree();

		bool Insert( const TValue& v  );
		const TValue* Find( const TValue& v  ) const;
		void PrintPreOrder();

		void PrintAsPNG( const std::string& filename ) const;


	protected:
		Node* m_Root;

	};


}

#include "kDTree.hxx"



#endif