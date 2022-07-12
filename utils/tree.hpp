#ifndef TREE_HPP
# define TREE_HPP

# include <iostream>
# include <memory>
# include <queue>

# include "node.hpp"
# include "../iterators/tree_iterator.hpp"
# include "../iterators/tree_reverse_iterator.hpp"
# include "pair.hpp"


namespace ft 
{

	template<class Value, class Compare, class Alloc = std::allocator<Value> >
	class RBTree 
	{
		public:
			typedef				Value													value_type;

			typedef				node<value_type>										Node;
			typedef				node<value_type> *										node_pointer;

			typedef				Alloc													pair_allocator_type;
			typedef typename	Alloc::template rebind<Node>::other						node_allocator_type;
			typedef				Compare													key_compare;

			typedef				ft::tree_iterator<Node, value_type>						iterator;
			typedef				ft::tree_reverse_iterator<iterator>						reverse_iterator;
			typedef				ft::tree_iterator<Node, const value_type, value_type>	const_iterator;
			typedef				ft::tree_reverse_iterator<const_iterator>				const_reverse_iterator;

		private:
			Node					top;
			node_pointer			root;
			key_compare				compare;
			node_allocator_type		alloc_node;
			pair_allocator_type		alloc_pair;
			
			// left rotates the given node
			void	leftRotate(node_pointer x) 
			{
				// new parent will be node's right child
				node_pointer	nParent = x->right;
			
				// update root if current node is root
				if (x == root)
					root = nParent;

				x->moveDown(nParent);

				// connect x with new parent's left element
				x->right = nParent->left;
				// connect new parent's left element with node
				// if it is not null
				if (nParent->left != NULL)
					nParent->left->parent = x;
			
				// connect new parent with x
				nParent->left = x;
			}
			
			void	rightRotate(node_pointer x) 
			{
				// new parent will be node's left child
				node_pointer	nParent = x->left;
			
				// update root if current node is root
				if (x == root)
					root = nParent;
			
				x->moveDown(nParent);
			
				// connect x with new parent's right element
				x->left = nParent->right;
				// connect new parent's right element with node
				// if it is not null
				if (nParent->right != NULL)
					nParent->right->parent = x;
			
				// connect new parent with x
				nParent->right = x;
			}
			
			void	swapColors(node_pointer x1, node_pointer x2) 
			{
				COLOR	temp;
				temp = x1->color;
				x1->color = x2->color;
				x2->color = temp;
			}

			void	swapNodes(node_pointer u, node_pointer v) 
			{
				Node tmp_v;

				// swap these nodes
				tmp_v.parent = v->parent;
				tmp_v.left = v->left;
				tmp_v.right = v->right;

				v->left = u->left;
				v->right = u->right;
				v->parent = u->parent;

				if (tmp_v.left == u)
					u->left = v;
				else
					u->left = tmp_v.left;
				if (tmp_v.right == u)
					u->right = v;
				else
					u->right = tmp_v.right;
				u->parent = tmp_v.parent;

				if (v->left != NULL)
					v->left->parent = v;
				if (v->right != NULL)
					v->right->parent = v;
				if (u->left != NULL)
					u->left->parent = u;
				if (u->right != NULL)
					u->right->parent = u;

				if (u->parent != NULL && u->parent->left == v)
					u->parent->left = u;
				if (u->parent != NULL && u->parent->right == v)
					u->parent->right = u;
				if (v->parent != NULL && v->parent->left == u)
					v->parent->left = v;
				if (v->parent != NULL && v->parent->right == u)
					v->parent->right = v;

				if (v == getRoot())
					root = u;
				else if (u == getRoot())
					root = v;
			}
			
			// fix red red at given node
			void	fixRedRed(node_pointer x) 
			{
				// if x is root color, make it black and return
				if (x == root) 
				{
					x->color = BLACK;
					return;
				}
			
				// initialize parent, grandparent, uncle
				node_pointer	parent = x->parent;
				node_pointer	grandparent = parent->parent;
				node_pointer	uncle = x->uncle();
			
				if (parent->color == RED) 
				{
					if (uncle != NULL && uncle->color == RED) 
					{
						// uncle red, perform recoloring and recurse
						parent->color = BLACK;
						uncle->color = BLACK;
						grandparent->color = RED;
						fixRedRed(grandparent);
					}
					else 
					{
						// Else perform LR, LL, RL, RR
						if (parent->isOnLeft()) 
						{
							if (x->isOnLeft()) 
							{
								// for left right
								swapColors(parent, grandparent);
							}
							else 
							{
								leftRotate(parent);
								swapColors(x, grandparent);
							}
							// for left left and left right
							rightRotate(grandparent);
						}
						else 
						{
							if (x->isOnLeft()) 
							{
								// for right left
								rightRotate(parent);
								swapColors(x, grandparent);
							}
							else 
								swapColors(parent, grandparent);
					
							// for right right and right left
							leftRotate(grandparent);
						}
					}
				}
			}
			
			// find node that do not have a left child
			// in the subtree of the given node
			node_pointer	successor(node_pointer x) 
			{
				node_pointer	temp = x;
			
				while (temp->left != NULL)
					temp = temp->left;
			
				return (temp);
			}
			
			// find node that replaces a deleted node in BST
			node_pointer	BSTreplace(node_pointer x) 
			{
				// when node have 2 children
				if (x->left != NULL && x->right != NULL)
					return (successor(x->right));
			
				// when leaf
				if (x->left == NULL && x->right == NULL)
					return (NULL);
			
				// when single child
				if (x->left != NULL)
					return (x->left);
				else
					return (x->right);
			}
			
			// deletes the given node
			void	deleteNode(node_pointer v) 
			{
				node_pointer	u = BSTreplace(v);

				// True when u and v are both black
				bool	uvBlack = ((u == NULL || u->color == BLACK) && (v->color == BLACK));
				node_pointer	parent = v->parent;

				if (u == NULL) 
				{
					// u is NULL therefore v is leaf
					if (v == root) 
					{
						// v is root, making root null
						root = NULL;
					}
					else {
						if (uvBlack) 
						{
							// u and v both black
							// v is leaf, fix double black at v
							fixDoubleBlack(v);
						}
						else 
						{
							// u or v is red
							if (v->sibling() != NULL) 
							{
								// sibling is not null, make it red"
								v->sibling()->color = RED;
							}
						}
						// delete v from the tree
						if (v->isOnLeft())
							parent->left = NULL;
						else
							parent->right = NULL;
					}
					alloc_node.deallocate(v, 1);
					return;
				}
				if (v->left == NULL || v->right == NULL) 
				{
					// v has 1 child
					if (v == root) 
					{
						// v is root, assign the value of u to v, and delete u
						alloc_pair.construct(&v->val, u->val);
						// v->val = u->val;
						v->left = NULL;
						v->right = NULL;
						alloc_node.deallocate(u, 1);
					}
					else 
					{
						// Detach v from tree and move u up
						if (v->isOnLeft())
							parent->left = u;
						else
							parent->right = u;
						alloc_node.deallocate(v, 1);
						u->parent = parent;
						if (uvBlack) 
						{
							// u and v both black, fix double black at u
							fixDoubleBlack(u);
						}
						else 
						{
							// u or v red, color u black
							u->color = BLACK;
						}
					}
					return;
				}
				// v has 2 children, swap values with successor and recurse
				swapNodes(u, v);
				deleteNode(v);
			}
			
			void	fixDoubleBlack(node_pointer x) 
			{
				if (x == root) 
				{
					// Reached root
					return;
				}
			
				node_pointer	sibling = x->sibling();
				node_pointer	parent = x->parent;
				if (sibling == NULL) 
				{
					// No sibiling, double black pushed up
					fixDoubleBlack(parent);
				}
				else 
				{
					if (sibling->color == RED) 
					{
						// Sibling red
						parent->color = RED;
						sibling->color = BLACK;
						if (sibling->isOnLeft()) 
						{
							// left case
							rightRotate(parent);
						}
						else 
						{
							// right case
							leftRotate(parent);
						}
						fixDoubleBlack(x);
					}
					else 
					{
						// Sibling black
						if (sibling->hasRedChild()) 
						{
							// at least 1 red children
							if (sibling->left != NULL && sibling->left->color == RED) 
							{
								if (sibling->isOnLeft()) 
								{
									// left left
									sibling->left->color = sibling->color;
									sibling->color = parent->color;
									rightRotate(parent);
								}
								else 
								{
									// right left
									sibling->left->color = parent->color;
									rightRotate(sibling);
									leftRotate(parent);
								}
							}
							else 
							{
								if (sibling->isOnLeft()) 
								{
									// left right
									sibling->right->color = parent->color;
									leftRotate(sibling);
									rightRotate(parent);
								}
								else 
								{
									// right right
									sibling->right->color = sibling->color;
									sibling->color = parent->color;
									leftRotate(parent);
								}
							}
							parent->color = BLACK;
						}
						else 
						{
							// 2 black children
							sibling->color = RED;
							if (parent->color == BLACK)
								fixDoubleBlack(parent);
							else
								parent->color = BLACK;
						}
					}
				}
			}
			
			// prints level order for given node
			void	levelOrder(node_pointer x) 
			{
				if (x == NULL) 
				{
					// return if node is null
					return;
				}
			
				// queue for level order
				std::queue<node_pointer>	q;
				node_pointer				curr;
			
				// push x
				q.push(x);
			
				while (!q.empty()) 
				{
					// while q is not empty
					// dequeue
					curr = q.front();
					q.pop();
				
					// print node value
					std::cout << curr->val << " ";
				
					// push children to queue
					if (curr->left != NULL)
						q.push(curr->left);
					if (curr->right != NULL)
						q.push(curr->right);
				}
			}

			void	inorder(node_pointer x) 
			{
				if (x == NULL)
					return;
				inorder(x->left);
				std::cout << x->val.first <<  "/" << x->val.second << std::endl;
				inorder(x->right);
			}

			bool	hintIsUseful(value_type n, node_pointer pos) 
			{
				if ((compare(n, root->val) && compare(pos->val, root->val)) || (compare(root->val, n) && compare(root->val, pos->val))) 
				{
					if ((!pos->isOnLeft() && compare(pos->parent->val, n)) || (pos->isOnLeft() && compare(n, pos->parent->val))) 
					{
						if ((!pos->parent->isOnLeft() && (compare(pos->parent->parent->val, n) || pos->parent == root)) || 
							(pos->parent->isOnLeft() && (compare(n, pos->parent->parent->val) || pos->parent == root))) 
								return (true);
					}
				}
				return (false);
			}
		
		public:
			/* constructor */
			RBTree() { root = NULL; }

			/* operator overload */
			RBTree &		operator=(const RBTree &in) 
			{
				alloc_pair.construct(&top.val, in.top.val);
				top.left = in.top.left;
				top.right = in.top.right;
				top.parent = in.top.parent;
				top.color = in.top.color;
				root = in.root;
				root->parent = &top;
				compare = in.compare;
				alloc_node = in.alloc_node;
				alloc_pair = in.alloc_pair;
				return (*this);
			}

			/* iterator */
			reverse_iterator 		rbegin() { return reverse_iterator(end()); }
			const_reverse_iterator	rbegin() const { return const_reverse_iterator(end()); }

			reverse_iterator		rend() { return reverse_iterator(begin()); }
			const_reverse_iterator	rend() const { return const_reverse_iterator(begin()); }

			iterator				end() 
			{
				if (root == NULL) 
				{
					return (iterator(&top));
				}
				return (iterator(&top));
			}

			const_iterator			end() const 
			{
				if (root == NULL) 
				{
					return (const_iterator(root));
				}
				return (const_iterator(root->parent));
			}

			iterator				begin() 
			{
				if (root == NULL)
					return (iterator(root));
				node_pointer	tmp = root;
				while (tmp->left != NULL)
					tmp = tmp->left;
				return (iterator(tmp));
			}

			const_iterator			begin() const 
			{
				if (root == NULL)
					return (const_iterator(root));
				node_pointer	tmp = root;
				while (tmp->left != NULL)
					tmp = tmp->left;
				return (const_iterator(tmp));
			}
			/* iterator */
			
			int				erase(iterator position) { return (deleteByVal(*position)); }

			node_pointer	getRoot() const { return (root); }

			size_t			max_size() const { return (alloc_node.max_size()); }
			
			// searches for given value
			// if found returns the node (used for delete)
			// else returns the last node while traversing (used in insert)
			node_pointer	search(value_type n, const node_pointer start) const 
			{
				node_pointer	temp = start;
				while (temp != NULL) 
				{
					if (compare(n, temp->val)) 
					{
						if (temp->left == NULL)
							break;
						else
							temp = temp->left;
					}
					else if (!compare(n, temp->val) && !compare(temp->val, n)) 
					{
						break;
					}
					else 
					{
						if (temp->right == NULL)
							break;
						else
							temp = temp->right;
					}
				}
				return (temp);
			}
			
			// inserts the given value to tree
			ft::pair<iterator, bool>	insert(value_type n) 
			{
				node_pointer	newNode = alloc_node.allocate(1);
				alloc_pair.construct(&newNode->val, n);

				newNode->left = NULL;
				newNode->right = NULL;
				newNode->parent = NULL;
				newNode->color = RED;

				if (root == NULL) 
				{
					// when root is null
					// simply insert value at root
					newNode->color = BLACK;
					root = newNode;
					root->parent = &top;
					top.left = root;
					top.right = NULL;
				}
				else 
				{
					node_pointer	temp = search(n, root);
				
					if (!compare(temp->val, n) && !compare(n, temp->val)) 
					{
						// return if value already exists
						alloc_node.deallocate(newNode, 1);
						return (ft::make_pair<iterator, bool>(iterator(temp), false));
					}
				
					// if value is not found, search returns the node
					// where the value is to be inserted
				
					// connect new node to correct node
					newNode->parent = temp;
				
					if (compare(n, temp->val))
						temp->left = newNode;
					else
						temp->right = newNode;
				
					// fix red red violation if exists
					fixRedRed(newNode);
				}
				return (ft::make_pair<iterator, bool>(iterator(newNode), true));
			}

			// inserts the given value to tree
			ft::pair<iterator, bool>	insert_hint(value_type n, node_pointer pos) 
			{
				node_pointer	newNode = alloc_node.allocate(1);
				alloc_pair.construct(&newNode->val, n);

				newNode->color = RED;
				newNode->left = NULL;
				newNode->right = NULL;
				newNode->parent = NULL;

				if (root == NULL) 
				{
					// when root is null
					// simply insert value at root
					newNode->color = BLACK;
					root = newNode;
					root->parent = &top;
					top.left = root;
					top.right = NULL;
				}
				else 
				{
					node_pointer	temp;
					if (hintIsUseful(n, pos))
						temp = search(n, pos);
					else
						temp = search(n, root);
				
					if (!compare(temp->val, n) && !compare(n, temp->val)) 
					{
						// return if value already exists
						alloc_node.deallocate(newNode, 1);
						return (ft::make_pair<iterator, bool>(iterator(temp), false));
					}
				
					// if value is not found, search returns the node
					// where the value is to be inserted
				
					// connect new node to correct node
					newNode->parent = temp;
				
					if (compare(n, temp->val))
						temp->left = newNode;
					else
						temp->right = newNode;
				
					// fix red red voilaton if exists
					fixRedRed(newNode);
				}
				return (ft::make_pair<iterator, bool>(iterator(newNode), true));
			}
			
			// utility function that deletes the node with given value
			int	deleteByVal(value_type n) 
			{
				if (root == NULL) {
					// Tree is empty
					return (0);
				}
			
				node_pointer	v = search(n, root);
				// node_pointer	u;
			
				if (!(!compare(v->val, n) && !compare(n, v->val))) 
				{
					// No node found to delete
					return (0);
				}
			
				deleteNode(v);
				return (1);
				// top->left = root;
			}
	};

}

#endif