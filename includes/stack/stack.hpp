#ifndef STACK_HPP
#define STACK_HPP

#include "vector.hpp"

namespace ft
{
    template <class T, class Container = ft::vector<T> >
    class stack
    {

    public:
        typedef Container container_type;
        typedef typename Container::value_type value_type;
        typedef typename Container::size_type size_type;
        typedef typename Container::reference reference;
        typedef typename Container::const_reference const_reference;

    protected:
        Container c;

    public:
        explicit stack(const Container &underlying = Container()): c(underlying) { }
        bool empty() const { return c.empty(); }
        size_type size() const { return c.size(); }
        value_type &top() { return c.back(); }
        const value_type &top() const { return c.back(); }
        void push(const value_type &x) { c.push_back(x); }
        void pop() { c.pop_back(); }


    template <class U, class c>
	friend bool operator==(const stack<U, c> &x,const stack<U, c> &y);
	template <class U, class c>
	friend bool operator<(const stack<U, c> &x,const stack<U, c> &y);

    
    };

    template <class T, class Container>
    bool operator==(const stack<T, Container> &x,const stack<T, Container> &y);
  
  	template <class T, class Container>
	bool operator==(const stack<T, Container>& lhs, const stack<T, Container>& rhs)
	{
		if (lhs.size() != rhs.size())
			return (false);
		return (ft::equal(lhs.c.begin(), lhs.c.end(), rhs.c.begin()));
	}
	template <class T, class Container>
	bool operator!=(const stack<T, Container>& lhs, const stack<T, Container>& rhs)
	{
		return !(lhs == rhs);
	}
	template <class T, class Container>
	bool operator<(const stack<T, Container>& lhs, const stack<T, Container>& rhs)
	{
		return (ft::lexicographical_compare(lhs.c.begin(), lhs.c.end(), rhs.c.begin(), rhs.c.end()));
	}
	template <class T, class Container>
	bool operator>(const stack<T, Container>& lhs, const stack<T, Container>& rhs)
	{
		return (rhs < lhs);
	}
	template <class T, class Container>
	bool operator>=(const stack<T, Container>& lhs, const stack<T, Container>& rhs)
	{
		return (!(lhs < rhs));
	}

	template <class T, class Container>
	bool operator<=(const stack<T, Container>& lhs,const stack<T, Container>& rhs)
	{
		return (!(rhs < lhs));
	}
}

#endif