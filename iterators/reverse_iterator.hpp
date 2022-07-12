#ifndef REVERSE_ITERATOR_HPP
#define REVERSE_ITERATOR_HPP

#include "./iterator_traits.hpp"

namespace ft
{
	template < class Iterator >
	class reverse_iterator
	{
		public:
			typedef Iterator															iterator_type;
			typedef typename ft::iterator_traits<iterator_type>::iterator_category		iterator_category;
			typedef typename ft::iterator_traits<iterator_type>::value_type 			value_type;
			typedef typename ft::iterator_traits<iterator_type>::difference_type		difference_type;
			typedef typename ft::iterator_traits<iterator_type>::pointer				pointer;
			typedef typename ft::iterator_traits<iterator_type>::reference				reference;

		private:
			iterator_type																_current;

		public:
			//Constructors
			reverse_iterator() : _current() { return; };
			explicit reverse_iterator (iterator_type it) : _current(it) { return; };
			template <class Itr>
			reverse_iterator (const reverse_iterator<Itr>& rev_it) { _current = rev_it.base(); return; };

			//Operators
			iterator_type base() const { return(_current); };
			reference operator*() const { iterator_type result = _current; return (*--result); };
			reverse_iterator operator+ (difference_type n) const 
			{ 
				return(reverse_iterator(_current - n));
			};

			reverse_iterator& operator++() { --_current; return(*this); };

			reverse_iterator operator++(int) 
			{ 
				reverse_iterator result = *this;
				--_current; 
				return(result); 
			};

			reverse_iterator& operator+= (difference_type n) { _current -= n; return(*this); };
			reverse_iterator operator- (difference_type n) const { return(reverse_iterator(_current.operator+(n))); };
			reverse_iterator& operator--() { ++_current; return(*this); };

			reverse_iterator  operator--(int) 
			{  
				reverse_iterator result = *this;
				++_current; 
				return(result); 
			};

			reverse_iterator& operator-= (difference_type n) { _current += n; return(*this); };
			pointer operator->() const { return &(operator*()); };
			reference operator[] (difference_type n) const { return (base()[-1 - n]); };
	};
	template <class Iterator>
	bool operator== (const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs)
	{
		if (lhs.base() == rhs.base())
			return (true);
		return (false);		
	}

	template <typename T, typename U>
	bool operator== (const reverse_iterator<T> lhs, reverse_iterator<U> rhs)
	{
		if (lhs.base() == rhs.base())
			return (true);
		return (false);		
	}

	template <class Iterator>
	bool operator!= (const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs)
	{
		if (lhs.base() != rhs.base())
			return (true);
		return (false);		
	}

	template <typename T, typename U>
	bool operator!= (const reverse_iterator<T>& lhs, const reverse_iterator<U>& rhs)
	{
		if (lhs.base() != rhs.base())
			return (true);
		return (false);		
	}

	template <class Iterator>
	bool operator< (const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs)
	{
		if (lhs.base() > rhs.base())
			return (true);
		return (false);		
	}

	template <typename T, typename U>
	bool operator< (const reverse_iterator<T>& lhs, const reverse_iterator<U>& rhs)
	{
		if (lhs.base() > rhs.base())
			return (true);
		return (false);		
	}

	template <class Iterator>
	bool operator<= (const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs)
	{
		if (lhs.base() >= rhs.base())
			return (true);
		return (false);		
	}

	template <typename T, typename U>
	bool operator<= (const reverse_iterator<T>& lhs, const reverse_iterator<U>& rhs)
	{
		if (lhs.base() >= rhs.base())
			return (true);
		return (false);		
	}

	template <class Iterator>
	bool operator> (const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs)
	{
		if (lhs.base() < rhs.base())
			return (true);
		return (false);		
	}

	template <typename T, typename U>
	bool operator> (const reverse_iterator<T>& lhs, const reverse_iterator<U>& rhs)
	{
		if (lhs.base() < rhs.base())
			return (true);
		return (false);		
	}

	template <class Iterator>
	bool operator>= (const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs)
	{
		if (lhs.base() <= rhs.base())
			return (true);
		return (false);		
	}

	template <typename T, typename U>
	bool operator>= (const reverse_iterator<T>& lhs, const reverse_iterator<U>& rhs)
	{
		if (lhs.base() <= rhs.base())
			return (true);
		return (false);		
	}

	template <class Iterator>
	reverse_iterator<Iterator> operator+(typename ft::reverse_iterator<Iterator>::difference_type n, const ft::reverse_iterator<Iterator>& it)
	{
		return (it + n);
	}

	template <typename T, typename U>
	reverse_iterator<T> operator+(const ft::reverse_iterator<T>& it, typename ft::reverse_iterator<U>::difference_type n)
	{
		return (it + n);
	}

	template <class Iterator>
	typename reverse_iterator<Iterator>::difference_type operator-(const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs)
	{
		return (rhs.base() - lhs.base());
	}

	template <typename T, typename U>
	typename reverse_iterator<T>::difference_type operator-(const reverse_iterator<T>& lhs, const reverse_iterator<U>& rhs)
	{
		return (rhs.base() - lhs.base());
	}
}

#endif
