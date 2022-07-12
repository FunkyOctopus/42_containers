#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <cstdlib>
#include <iostream>
#include <memory>
#include <stdexcept>

#include "../iterators/vector_iterator.hpp"
#include "../iterators/reverse_iterator.hpp"

#include "../utils/algorithm.hpp"
#include "../utils/enable_if.hpp"

namespace ft
{
	template < class T, class allocator = std::allocator<T> >
	class vector
	{
		public:
			typedef T												value_type;	
			typedef allocator										allocator_type;
			typedef typename allocator_type::reference				reference;
			typedef typename allocator_type::const_reference		const_reference;
			typedef typename allocator_type::pointer				pointer;
			typedef typename allocator_type::const_pointer			const_pointer;

			typedef	typename ft::vector_iterator<value_type>		iterator;
			typedef	typename ft::vector_iterator<const value_type>	const_iterator;
			typedef typename ft::reverse_iterator<iterator>			reverse_iterator;
			typedef typename ft::reverse_iterator<const_iterator>	const_reverse_iterator;

			typedef typename ft::iterator_traits<iterator>::difference_type		difference_type;
			typedef typename allocator_type::size_type							size_type;

		private:
			size_type												_size;
			size_type 												_capacity;
			allocator_type											_alloc;
			pointer													_begin;
			pointer													_end;

		public:
			//Constructors
			explicit vector(const allocator_type& alloc = allocator_type()) :
			_size(0), _capacity(0), _alloc(alloc), _begin(NULL) {};

			explicit vector(size_type n, const T& val = value_type(), const allocator_type& alloc = allocator_type()) : 
			_size(n), _capacity(n), _alloc(alloc), _begin(NULL), _end(NULL)
			{
				_begin = _alloc.allocate(n * sizeof(size_type));
				_end = _begin + _size;
				for (size_type i = 0; i < n; ++i)
					_alloc.construct(_begin + i, val);		
			};

			template <class InputIterator>
         	vector(InputIterator first, InputIterator last, const allocator_type& alloc = allocator(),
						typename ft::enable_if<!ft::is_integral<InputIterator>::value>::type = true) :
							_size(0), _capacity(0), _alloc(alloc), _begin(NULL), _end(NULL)
			{
				InputIterator temp = first;
				while (temp != last)
				{
					++temp;
					++_size;
				}
				_capacity = _size;
				_begin = _alloc.allocate(_capacity * sizeof(size_type));
				_end = _begin + _size;	
				int i = 0;		
				while (first != last)
				{
					_alloc.construct(_begin + i, *first);
					++first;
					++i;
				}					
			};

			vector(const vector& x)
			{ 
				_size = x._size; 
				_capacity = x._capacity; 
				_alloc = x._alloc; 
				_begin = _alloc.allocate(_capacity * sizeof(size_type));
				_end = _begin + _size;

				for (size_type i = 0; i < _size; ++i)
					_alloc.construct(_begin + i, x[i]);
			};

			~vector()
			{ 
				if (_begin)
				{
					clear();
					_alloc.deallocate(_begin, _capacity);
				}
			};

			vector & operator=( vector const & other ) 
			{ 
				clear();
                _alloc.deallocate(_begin, _capacity);

				_size = other._size; 
				_capacity = other._capacity; 
				_alloc = other._alloc;
				_begin = _alloc.allocate(_capacity * sizeof(size_type));
				_end = _begin + _size;

				for (size_type i = 0; i < _size; ++i)
					_alloc.construct(_begin + i, other[i]);

				return (*this); 
			}


			//Iterators
			iterator begin() { return(iterator(_begin)); };
			const_iterator begin() const { return(const_iterator(_begin)); };
			iterator end() { return(_begin + _size); };
			const_iterator end() const { return(const_iterator(_begin + _size)); };
			reverse_iterator rbegin() { return(reverse_iterator(end())); };
			const_reverse_iterator rbegin() const { return(const_reverse_iterator(end())); };
			reverse_iterator rend() { return(reverse_iterator(begin())); };
			const_reverse_iterator rend() const { return(const_reverse_iterator(begin())); };


			//Capacity
			size_type size() const { return(_size); };
			size_type max_size() const { return(_alloc.max_size()); };

			void resize(size_type n, value_type val = value_type()) 
			{ 
				pointer		new_begin;
				size_type	old_capacity;

				if (n > max_size())
					throw std::length_error("vector");
				old_capacity = _capacity;
				if (_size > n)
					for (size_type i = _size - 1; i >= (size_type)n; i--)
						_alloc.destroy(_begin + i);
				else if (_capacity < n)
				{
					if (!_capacity)
						_capacity = n;
					while (_capacity < n)
						_capacity *= 2;
					new_begin = _alloc.allocate(_capacity);
					for (size_type i = 0; i < _size; i++)
						_alloc.construct(new_begin + i, _begin[i]);
					for (size_type i = _size; i < n; i++)
						_alloc.construct(new_begin + i, val);
					for (size_type i = 0; i < _size; i++)
						_alloc.destroy(_begin + i);
					_alloc.deallocate(_begin, old_capacity);
					_begin = new_begin;
				}
				else
					for (size_type i = _size; i < n; i++)
						_alloc.construct(_begin + i, val);
				_size = n;
			};

			size_type capacity() const { return(_capacity); };
			bool empty() const 
			{ 
				if (_size == 0)
					return (true);
				return (false);  
			};

			void reserve(size_type n)
			{
				if (n > _alloc.max_size())
					throw std::length_error("can't allocate region");
				if (n <= _capacity)
					return ;
				pointer	new_begin = _alloc.allocate(n);
				for (size_t i = 0; i < _size; i++)
					_alloc.construct(&new_begin[i], _begin[i]);
				for (size_t i = 0; i < _size; i++)
					_alloc.destroy(&(_begin[i]));
				_alloc.deallocate(_begin, _capacity);
				_begin = new_begin;
				_capacity = n;
			};

			//Element access
			reference operator[] (size_type n) { return(*(_begin + n)); };
			const_reference operator[] (size_type n) const { return(*(_begin + n)); };

			reference at(size_type n) 
			{ 
				if (n < 0 || n >= _size)
					throw std::out_of_range("vector");
				return(*(_begin + n));
			};

			const_reference at(size_type n) const 
			{  
				if (n < 0 || n >= _size)
					throw std::out_of_range("vector");
				return(*(_begin + n));
			};

			reference front() { return(*(_begin)); };
			const_reference front() const { return(*(_begin)); };
			reference back() { return(*(_begin + _size - 1)); };
			const_reference back() const { return(*(_begin + _size - 1)); };

			//Modifiers
			template <class InputIterator>
  			void assign(InputIterator first, InputIterator last,
					typename ft::enable_if<!ft::is_integral<InputIterator>::value>::type = true)
			{
				clear();
				for ( ; first != last; ++first)
					push_back(*first);
			};

			void assign(size_type n, const value_type& val) 
			{
				clear();
				for (size_type i = 0; i < n; ++i)
					push_back(val);
			};

			void push_back(const value_type& val) { resize(_size + 1, val); };
			
			void pop_back() { erase(_begin + _size - 1); };

			iterator insert(iterator position, const value_type& val) 
			{
				if (_size == 0)
				{
					push_back(val);
					return (_begin);
				}
				size_type posindex = position - _begin;

				while(posindex > _size)
					push_back(0);
				resize(_size + 1);

				for (size_type i = _size - 1; i >= posindex; --i)
					_begin[i] = _begin[i - 1];

				_begin[posindex] = val;
				return (_begin + posindex);
			};

    		void insert(iterator position, size_type n, const value_type& val)
			{
				size_type oldSize = _size;
				size_type posindex = position - _begin;

				if (posindex > _size)
					resize(_size + posindex);
				else if (_size == 0)
				{
					for (size_type i = 0; i < n; ++i)
						push_back(val);
					return ;
				}
				else
					resize(_size + n);

				int j = 0;
				for (size_type i = _size - 1; i > oldSize - 1; --i)
				{
					if (oldSize - j > 0)
						_begin[i] = _begin[oldSize - 1 - j];
					++j;
				}
				for (size_type i = 0; i < n; ++i)
					_begin[posindex + i] = val;
			};

			template <class InputIterator>
    		void insert(iterator position, InputIterator first, InputIterator last,
						typename ft::enable_if<!ft::is_integral<InputIterator>::value>::type = true)
			{
				size_type posindex = position - _begin;
				size_type n = ft::distance(first, last);
				size_type oldSize = _size;
				resize(_size + n);
				int j = 0;

				for (size_type i = _size - 1; i > (_size - n - (oldSize - posindex)); --i)
				{
					if (oldSize - j > 0)
						_begin[i] = _begin[oldSize - 1 - j];
					++j;
				}

				for (size_type i = 0; i < n; ++i)
				{
					_begin[posindex + i] = *first;
					++first;
				}
			};

			iterator erase(iterator position)
			{
				for (size_type pos = (position - _begin); pos < (_size - 1); ++pos)
					_begin[pos] = _begin[pos + 1];
				_alloc.destroy(_begin + _size - 1);
				_size -= 1;
				return (position);
			};

			iterator erase(iterator first, iterator last)
			{
				size_type i = 0;
				size_type start = (first - _begin);
				size_type end = (last - _begin);

				for (iterator it = _begin + end; it != _end; ++it)
				{
					_begin[start + i] = _begin[end + i];
					++i;
				}
				while (end != _size)
				{
					_alloc.destroy(_begin + end);					
					++end;
				}
				_size -= (last - first);
				return (first);
			};

			void swap(vector& x)
			{
				size_type			tempSize = _size;
				size_type 			tempCap = _capacity;
				allocator_type		tempAlloc = _alloc;
				iterator			tempBegin = _begin;
				iterator			tempEnd = _end;

				_size = x._size;
				_capacity = x._capacity;
				_alloc = x._alloc;
				_begin = x._begin;
				_end = x._end;

				x._size = tempSize;
				x._capacity = tempCap;
				x._alloc = tempAlloc;
				x._begin = tempBegin.base();
				x._end = tempEnd.base();			
			};

			void clear()
			{
				for (size_type i = 0; i < _size; ++i)
					_alloc.destroy(_begin + i);
				_size = 0;
			};

			//Allocator
			allocator_type get_allocator() const { return(_alloc); };
	};
	template <class T, class Alloc>
	bool operator== (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs) 
	{ 
		if (lhs.size() != rhs.size())
			return (false);
		bool result = ft::equal(lhs.begin(), lhs.end(), rhs.begin());
		return (result);
	};

	template <class T, class Alloc>
	bool operator!= (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
	{
		if (lhs.size() != rhs.size())
			return (true);
		bool result = ft::equal(lhs.begin(), lhs.end(), rhs.begin());
		return (!result);
	};

	template <class T, class Alloc>
	bool operator<  (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
	{
		if (ft::lexicographical_compare (lhs.begin(), lhs.end(), rhs.begin(), rhs.end()))
			return (true);
		return (false);
	};

	template <class T, class Alloc>
	bool operator<= (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
	{
		if (lhs == rhs || lhs < rhs)
			return (true);
		return (false);
	};

	template <class T, class Alloc>
	bool operator>  (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
	{
		if (lhs == rhs || ft::lexicographical_compare (lhs.begin(), lhs.end(), rhs.begin(), rhs.end()))
			return (false);
		return (true);
	};

	template <class T, class Alloc>
	bool operator>= (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
	{
		if (lhs == rhs || lhs > rhs)
			return (true);
		return (false);
	};

	template <class T, class Alloc>
  	void swap (vector<T,Alloc>& x, vector<T,Alloc>& y)
	{
		vector<T,Alloc> temp;
		temp.swap(x);
		x.swap(y);
		y.swap(temp);
	}
}

#endif
