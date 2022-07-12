#ifndef VECTOR_ITERATOR_HPP
#define VECTOR_ITERATOR_HPP

#include "./iterator_traits.hpp"
#include "./iterator.hpp"

namespace ft
{
	template < class T >
	class vector_iterator : public ft::iterator<random_access_iterator_tag, T>
	{
		public:
			typedef typename ft::iterator<random_access_iterator_tag, T>::value_type 			value_type;
			typedef typename ft::iterator<random_access_iterator_tag, T>::difference_type		difference_type;
			typedef typename ft::iterator<random_access_iterator_tag, T>::pointer				pointer;
			typedef typename ft::iterator<random_access_iterator_tag, T>::reference				reference;
			typedef typename ft::iterator<random_access_iterator_tag, T>::iterator_category		iterator_category;


		protected:
			pointer																				ptr;

		public:
			//Constructors
			vector_iterator(pointer in = NULL) : ptr(in) { return; };
			vector_iterator (const vector_iterator &in) { ptr = in.ptr; return; };
			~vector_iterator() { return; };

			//Operators
			pointer base() const { return(ptr); };
			reference operator*() const { return (*ptr); };
			vector_iterator operator+ (difference_type n) const { return(ptr + n); };
			vector_iterator& operator++() { ++ptr; return(*this); };

			vector_iterator operator++(int) 
			{ 
				vector_iterator result = *this;
				++ptr; 
				return(result); 
			};

			vector_iterator& operator+=(difference_type n) { ptr += n; return(*this); };
			vector_iterator operator-(difference_type n) const { return(vector_iterator(ptr - n)); };
			difference_type operator-(vector_iterator const &in) { return((ptr - in.ptr)); }; /* needed? */
			
			vector_iterator& operator--() { --ptr; return(*this); };

			vector_iterator  operator--(int) 
			{  
				vector_iterator result = *this;
				--ptr; 
				return(result); 
			};

			vector_iterator& operator-= (difference_type n) { ptr -= n; return(*this); };
			pointer operator->() const { return &(operator*()); };
			reference operator[] (difference_type n) const { return (*(ptr + n)); };

			bool operator==(const vector_iterator &in) const
			{
				if (ptr == in.ptr)
					return (true);
				return (false);
			}

			bool operator!=(const vector_iterator &in) const
			{
				if (ptr != in.ptr)
					return (true);
				return (false);
			}

			bool operator<(const vector_iterator &in) const
			{
				if (ptr < in.ptr)
					return (true);
				return (false);
			}

			bool operator<=(const vector_iterator &in) const
			{
				if (ptr <= in.ptr)
					return (true);
				return (false);
			}

			bool operator>(const vector_iterator &in) const
			{
				if (ptr > in.ptr)
					return (true);
				return (false);
			}

			bool operator>=(const vector_iterator &in) const
			{
				if (ptr >= in.ptr)
					return (true);
				return (false);
			}

			vector_iterator  operator=(const vector_iterator &in) 
			{  
				ptr = in.ptr;
				return(*this); 
			}

			vector_iterator  operator+=(int i) 
			{  
				ptr += i;
				return(*this); 
			};

			vector_iterator  operator-=(int i) 
			{  
				ptr -= i;
				return(*this); 
			};

			operator vector_iterator<const T> () const
			{
				return(vector_iterator<const T>(ptr));
			}

	};

	template <typename T, typename U>
	bool operator==(const ft::vector_iterator<T> lhs, ft::vector_iterator<U> rhs)
	{
		if (lhs.base() == rhs.base())
			return (true);
		return (false);
	}

	template <typename T, typename U>
	bool operator!=(const ft::vector_iterator<T> lhs, ft::vector_iterator<U> rhs)
	{
		if (lhs.base() != rhs.base())
			return (true);
		return (false);
	}

	template <typename T, typename U>
	bool operator<(const ft::vector_iterator<T> lhs, ft::vector_iterator<U> rhs)
	{
		if (lhs.base() < rhs.base())
			return (true);
		return (false);
	}

	template <typename T, typename U>
	bool operator<=(const ft::vector_iterator<T> lhs, ft::vector_iterator<U> rhs)
	{
		if (lhs.base() <= rhs.base())
			return (true);
		return (false);
	}

	template <typename T, typename U>
	bool operator>(const ft::vector_iterator<T> lhs, ft::vector_iterator<U> rhs)
	{
		if (lhs.base() > rhs.base())
			return (true);
		return (false);
	}

	template <typename T, typename U>
	bool operator>=(const ft::vector_iterator<T> lhs, ft::vector_iterator<U> rhs)
	{
		if (lhs.base() >= rhs.base())
			return (true);
		return (false);
	}

	template <typename T>
	ft::vector_iterator<T> operator+(typename ft::vector_iterator<T>::difference_type lhs, ft::vector_iterator<T> rhs)
	{
		return (rhs + lhs);
	}

	template <typename T>
	typename ft::iterator_traits<T> operator-(typename ft::vector_iterator<T>::difference_type lhs, ft::vector_iterator<T> rhs)
	{
		return (lhs - rhs);
	}

	template <typename T>
	typename ft::iterator_traits<vector_iterator<T> >::difference_type operator-(const ft::vector_iterator<T> lhs, ft::vector_iterator<T> rhs)
	{
		return (lhs.base() - rhs.base());
	}

	template <typename T, typename U>
	typename ft::iterator_traits<vector_iterator<T> >::difference_type operator-(const ft::vector_iterator<T> lhs, ft::vector_iterator<U> rhs)
	{
		return (lhs.base() - rhs.base());
	}

	template<typename Iterator>
	typename ft::iterator_traits<Iterator>::difference_type distance(Iterator lhs, Iterator rhs)
	{
		typename ft::iterator_traits<Iterator>::difference_type diff = 0;
		while (lhs != rhs)
		{
			++diff;
			++lhs;
		}
		return (diff);
	}
}

#endif
