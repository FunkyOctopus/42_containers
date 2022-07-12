#ifndef TREE_NODE_HPP
# define TREE_NODE_HPP

#include <memory>

enum COLOR 
{
	BLACK,
	RED,
};

namespace ft 
{
 
	template<class T>
	class node 
	{

		public:
			typedef		T		value_type;
			typedef		node*	node_pointer;

		public:
			node_pointer	left;
			node_pointer	right;
			node_pointer	parent;
			value_type		val;
			COLOR			color;
		
			node() : val() 
			{
				parent = NULL;
				left = NULL;
				right = NULL;
				color = RED;
			}

			node(value_type val) : val(val) 
			{
				parent = NULL;
				left = NULL;
				right = NULL;
				color = RED;
			}
		
			// returns pointer to uncle
			node_pointer	uncle() 
			{
				// If no parent or grandparent, then no uncle
				if (parent == NULL || parent->parent == NULL)
					return (NULL);
				if (parent->isOnLeft()) // uncle on right
					return (parent->parent->right);
				else // uncle on left
					return (parent->parent->left);
			}
		
			// check if node is left child of parent
			bool	isOnLeft() { return (this == parent->left); }
			
			// returns pointer to sibling
			node_pointer	sibling() 
			{
				// sibling null if no parent
				if (parent == NULL)
					return (NULL);
				if (isOnLeft())
					return (parent->right);
				return (parent->left);
			}
		
			void	moveDown(node_pointer nParent) 
			{
				if (parent != NULL) 
				{
					if (isOnLeft())
						parent->left = nParent;
					else
						parent->right = nParent;
				}
				nParent->parent = parent;
				parent = nParent;
			}
		
			bool	hasRedChild() 
			{
				return ((left != NULL && left->color == RED) || (right != NULL && right->color == RED));
			}

	};
}

#endif