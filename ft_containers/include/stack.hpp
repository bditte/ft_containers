#ifndef STACK_HPP
# define STACK_HPP

# include "utils/utils.hpp"
# include "vector.hpp"

namespace ft
{
template<class T, class Container = ft::vector<T> >
class stack
{

public:
	// Member types
	typedef  Container										container_type;
	typedef typename Container::value_type					value_type;
	typedef typename Container::size_type					size_type;
	typedef typename Container::reference					reference;
	typedef typename Container::const_reference				const_reference;

	// Member functions

	explicit				stack(const Container& cont = Container()): c(cont)
	{}

	~stack()
	{}

	stack&					operator=(const stack& other)
	{ this->_map = other.c; return *this;	}

	// Element access

	reference				top()	{ return (this->c.back()); }
	const_reference			top() const { return (this->c.back()); }

	// Capacity

	bool					empty() const { return (this->c.empty()); }
	size_type				size() const	{ return (this->c.size()); }

	// Modifiers

	void					push(const value_type& value) { this->c.push_back(value); }
	void					pop() { this->c.pop_back(); }

	friend	bool operator==(const stack<T, Container> &lhs, const stack<T, Container> &rhs)
	{ 	return (lhs.c == rhs.c); }

	friend	bool operator< (const stack<T, Container> &lhs, const stack<T, Container> &rhs)
	{	return (lhs.c < rhs.c);	}

protected:
	container_type		c;

};

template< class T, class Container >
bool operator!=( const ft::stack<T,Container>& lhs, const ft::stack<T,Container>& rhs )
{	return !(lhs == rhs); }
	
template< class T, class Container >
bool operator<=( const ft::stack<T,Container>& lhs, const ft::stack<T,Container>& rhs )
{	return !(rhs < lhs); }

template< class T, class Container >
bool operator>( const ft::stack<T,Container>& lhs, const ft::stack<T,Container>& rhs )
{	return (rhs < lhs); }
template< class T, class Container >
bool operator>=( const ft::stack<T,Container>& lhs, const ft::stack<T,Container>& rhs )
{	return !(lhs < rhs); }


}

#endif