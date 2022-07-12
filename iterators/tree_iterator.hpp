#ifndef TREE_ITERATOR_HPP
# define TREE_ITERATOR_HPP

# include "iterator.hpp"

namespace ft 
{

	template<class T_node, class var_type , class var_type_no_const = var_type>
		class tree_iterator
		{
			public:
				typedef ptrdiff_t						difference_type;
				typedef T_node							value_type;
				typedef T_node *						pointer;
				typedef T_node &						reference;
				typedef ft::bidirectional_iterator_tag	iterator_category;
				typedef var_type						variable_type;
		
			private:
				pointer	ptr;

			public:
				tree_iterator(pointer iptr = nullptr) : ptr(iptr) {}

				tree_iterator(const tree_iterator &in) : ptr(in.ptr) {}

				tree_iterator(tree_iterator<value_type, var_type_no_const, var_type_no_const> in) : ptr(in.base()) {}

				~tree_iterator() {}

				pointer				base() const { return ptr; }

				variable_type &		operator*() { return ptr->val; }
				variable_type &		operator*() const { return ptr->val; }

				variable_type *		operator->() { return &(operator*()); }
				variable_type *		operator->() const { return &(operator*()); }

				tree_iterator &		operator++() 
				{
					if (!ptr)
						return (*this);
					if (ptr->right != NULL) 
					{
						ptr = ptr->right;
						while (ptr->left != NULL)
							ptr = ptr->left;
					}
					else
					{
						pointer	cur;
						cur = ptr->parent;
						while (cur != NULL && cur->right == ptr) 
						{
							ptr = cur;
							cur = ptr->parent;
						}
						ptr = cur;
					}
					return (*this);
				}

				tree_iterator &		operator--() 
				{
					if (!ptr)
						return (*this);
					if (ptr->left != NULL) 
					{
						ptr = ptr->left;
						while (ptr->right != NULL)
							ptr = ptr->right;
					}
					else 
					{
						pointer	cur;
						cur = ptr->parent;
						while (cur != NULL && cur->left == ptr) 
						{
							ptr = cur;
							cur = ptr->parent;
						}
						ptr = cur;
					}
					return (*this);
				}

				tree_iterator		operator++(int) 
				{
					tree_iterator	temp = *this;
					++(*this);
					return (temp);
				}
		
				tree_iterator		operator--(int) 
				{
					tree_iterator	temp = *this;
					--(*this);
					return (temp);
				}

				bool		operator==(const tree_iterator & in) 
				{
					return (base() == in.base());
				}
		
				bool		operator!=(const tree_iterator & in) 
				{
					return (base() != in.base());
				}
		};
}

#endif
