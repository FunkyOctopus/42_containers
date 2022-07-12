#ifndef ITERATORS_HPP
#define ITERATORS_HPP

namespace ft
{
	struct random_access_iterator_tag {};
	struct input_iterator_tag {};
	struct forward_iterator_tag 		: 	public input_iterator_tag {};	
	struct bidirectional_iterator_tag 	: 	public forward_iterator_tag {};

	template <class Category, class T, class Distance = ptrdiff_t, class Pointer = T*, class Reference = T&>
	struct iterator 
	{
		typedef Distance  difference_type;
		typedef T         value_type;
		typedef Pointer   pointer;
		typedef Reference reference;
		typedef Category  iterator_category;
  	};
}

#endif
