//
// Created by Namor Scarab on 3/8/22.
//

#ifndef FT_STACK_HPP
#define FT_STACK_HPP

#include "ft_vector.hpp"

namespace ft
{
	template<class T, class Container = ft::Vector<T> >
	class Stack
	{
	public:
        //================================typedef===================================
		typedef T			                            value_type;
		typedef Container	                            container_type;
		typedef typename container_type::size_type		size_type;
        //================================end typedef===============================
        //=============================private variables============================
    protected:
		container_type cont;
        //===========================end private variables==========================
	public:
        //============================constructors==================================
		explicit Stack (const container_type& c = container_type()) : cont(c) {}
        //======================end constructors====================================
        Stack& operator=( const Stack& other ) {
            cont = other.cont;
        }
        //=========================member functions=================================
		bool empty() const
        {
            return (cont.empty());
        }

		size_type size() const
        {
            return (cont.size());
        }

		value_type& top()
        {
            return (cont.back());
        }

		const value_type& top() const
        {
            return (cont.back());
        }

		void push (const value_type& val)
        {
            cont.push_back(val);
        }

		void pop()
        {
            cont.pop_back();
        }
        //=======================end member functions===============================
        //========================non member overloads==============================

		friend bool operator==(const Stack<T,Container>& lhs, const Stack<T,Container>& rhs)
		{
			return (lhs.cont == rhs.cont);
		}

		friend bool operator!=(const Stack<T,Container>& lhs, const Stack<T,Container>& rhs)
		{
			return (lhs.cont != rhs.cont);
		}

		friend bool operator< (const Stack<T,Container>& lhs, const Stack<T,Container>& rhs)
		{
			return (lhs.cont < rhs.cont);
		}

		friend bool operator<=(const Stack<T,Container>& lhs, const Stack<T,Container>& rhs)
		{
			return (lhs.cont <= rhs.cont);
		}

		friend bool operator> (const Stack<T,Container>& lhs, const Stack<T,Container>& rhs)
		{
			return (lhs.cont > rhs.cont);
		}

		friend bool operator>=(const Stack<T,Container>& lhs, const Stack<T,Container>& rhs)
		{
			return (lhs.cont >= rhs.cont);
		}
        //======================end non member overloads============================
	};
}


#endif //FT_STACK_HPP
