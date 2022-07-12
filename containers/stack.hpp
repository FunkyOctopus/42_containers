#ifndef STACK_HPP
#define STACK_HPP

#include <iostream>
#include <memory>

#include "vector.hpp"

namespace ft
{
	template < class T, class Container = ft::vector<T> >
	class stack
	{
		public:
			typedef typename Container::value_type			value_type;
			typedef	Container								container_type;
			typedef typename Container::size_type			size_type;
			typedef typename Container::reference			reference;
			typedef typename Container::const_reference		const_reference;

		protected:
			container_type c;

		private:

		public:
			explicit stack(const container_type& ctnr = container_type()) : c(ctnr) {};
			~stack() { c.clear(); }
			stack & operator=(stack const & other) { c = other.c; return (*this); }

			bool empty() const { return(c.empty()); }
			size_type size() const { return(c.size()); }
			reference top() { return(c.back()); }
			const_reference top() const { return(c.back()); }
			void push(const value_type& value) { c.push_back(value); }
			void pop() { c.pop_back(); }

			template <class TF, class ContainerF>
				friend bool operator== (const ft::stack<TF,ContainerF>& lhs, const ft::stack<TF,ContainerF>& rhs);
			template <class TF, class ContainerF>
				friend bool operator!= (const ft::stack<TF,ContainerF>& lhs, const ft::stack<TF,ContainerF>& rhs);
			template <class TF, class ContainerF>
				friend bool operator<  (const ft::stack<TF,ContainerF>& lhs, const ft::stack<TF,ContainerF>& rhs);
			template <class TF, class ContainerF>
				friend bool operator<= (const ft::stack<TF,ContainerF>& lhs, const ft::stack<TF,ContainerF>& rhs);
			template <class TF, class ContainerF>
				friend bool operator> (const ft::stack<TF,ContainerF>& lhs, const ft::stack<TF,ContainerF>& rhs);
			template <class TF, class ContainerF>
				friend bool operator>= (const ft::stack<TF,ContainerF>& lhs, const ft::stack<TF,ContainerF>& rhs);
	};
	template <class T, class Container>
		bool operator== (const ft::stack<T,Container>& lhs, const ft::stack<T,Container>& rhs) { if (lhs.c == rhs.c) return (true); return (false); };
	template <class T, class Container>
		bool operator!= (const ft::stack<T,Container>& lhs, const ft::stack<T,Container>& rhs) { if (lhs.c != rhs.c) return (true); return (false); };
	template <class T, class Container>
		bool operator< (const ft::stack<T,Container>& lhs, const ft::stack<T,Container>& rhs) { if (lhs.c < rhs.c) return (true); return (false); };
	template <class T, class Container>
		bool operator<= (const ft::stack<T,Container>& lhs, const ft::stack<T,Container>& rhs) { if (lhs.c <= rhs.c) return (true); return (false); };
	template <class T, class Container>
		bool operator> (const ft::stack<T,Container>& lhs, const ft::stack<T,Container>& rhs) { if (lhs.c > rhs.c) return (true); return (false); };
	template <class T, class Container>
		bool operator>= (const ft::stack<T,Container>& lhs, const ft::stack<T,Container>& rhs) { if (lhs.c >= rhs.c) return (true); return (false); };
}

#endif
