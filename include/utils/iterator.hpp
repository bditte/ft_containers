/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iterator.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bditte <bditte@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/08 09:17:09 by bditte            #+#    #+#             */
/*   Updated: 2022/04/05 16:31:00 by bditte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ITERATOR_HPP
# define ITERATOR_HPP

# include <cstddef>
# include "utils.hpp"

namespace ft
{

	/*
		Iterator base class
		Base class template used to derive iterator classes from it.
	*/

	template <class Category,
			class T,
			class Distance = std::ptrdiff_t, 
			class Pointer = T*,
			class Reference = T&>
	struct iterator
	{
		typedef T			value_type;
		typedef Distance	difference_type;
		typedef Pointer		pointer;
		typedef Reference	reference;
		typedef Category	iterator_category;
	};

	/*
		Iterator categories
		Empty classes to indentify the category of an iterator.
	*/

	struct	input_iterator_tag {};
	struct	output_iterator_tag {};
	struct	forward_iterator_tag {};	
	struct	random_access_iterator_tag {}; // Used for vector iterator
	struct	bidirectional_iterator_tag {}; // Used for map iterator
	
	/*
		Iterator traits
		Traits class defining properties of iterators.
	*/

	template <class Iterator> class iterator_traits
	{
		public:
			typedef	typename Iterator::difference_type				difference_type;
			typedef	typename Iterator::value_type					value_type;
			typedef typename Iterator::pointer						pointer;
			typedef typename Iterator::reference					reference;
			typedef typename Iterator::iterator_category			iterator_category;
	};

	template <class T> class iterator_traits<T*>
	{
		public:
			typedef	ptrdiff_t								difference_type;
			typedef	T										value_type;
			typedef T*										pointer;
			typedef T&										reference;
			typedef ft::random_access_iterator_tag			iterator_category;
	};

	template <class T> class iterator_traits<const T*>
	{
			public:
			typedef	ptrdiff_t								difference_type;
			typedef	T										value_type;
			typedef const T*								pointer;
			typedef const T&								reference;
			typedef ft::random_access_iterator_tag			iterator_category;
	};

	// Iterator functions

	template <class InputIterator>
	typename iterator_traits<InputIterator>::difference_type
	distance(InputIterator first, InputIterator last)
	{
		typename InputIterator::difference_type res = 0;

		while (first != last)
		{
			first++;
			res++;
		}
		return (res);
	}

	template <class InputIterator, class Distance>
	void	advance(InputIterator& it, Distance n)
	{
		while (n > 0)
		{
			it++;
			n--;
		}
		while (n < 0)
		{
			it--;
			n++;
		}
	}

	// Random access iterator implementation

	template <class T>
	class random_access_iterator : public ft::iterator<ft::random_access_iterator_tag, T>
	{
		private:
			typedef	random_access_iterator<T>							ra_iterator;
			typedef	iterator<ft::random_access_iterator_tag, T>			parent;
			
		public:
			typedef	T												value_type;
			typedef typename parent::difference_type				difference_type;
			typedef typename parent::pointer						pointer;
			typedef	typename parent::reference						reference;
			typedef typename parent::iterator_category				iterator_category;

			random_access_iterator(pointer src = NULL): ptr(src) {};
			random_access_iterator(const ra_iterator &src): ptr(src.ptr) {};
			~random_access_iterator() {};

			pointer						base() const { return (ptr); }

			ra_iterator&				operator=(const ra_iterator& rhs){ ptr = rhs.ptr; return (*this);}

			bool						operator==(const ra_iterator& rhs) const { return (ptr == rhs.ptr); }
			bool						operator!=(const ra_iterator& rhs) const { return (ptr != rhs.ptr); }
			bool						operator<(const ra_iterator& rhs) const { return (ptr < rhs.ptr); }
			bool						operator<=(const ra_iterator& rhs) const { return (ptr <= rhs.ptr); }
			bool						operator>(const ra_iterator& rhs) const { return (ptr > rhs.ptr); }
			bool						operator>=(const ra_iterator& rhs) const { return (ptr >= rhs.ptr); }
			
			reference					operator*() const { return (*ptr); }
			pointer						operator->() const { return (ptr); }
			reference					operator[](const difference_type n) const { return (*(ra_iterator(ptr + n))); }

			ra_iterator&				operator++(){ ++ptr; return(*this); }
			ra_iterator					operator++(int){ ra_iterator tmp = *this; ptr++; return (tmp);}
			ra_iterator&				operator--(){ --ptr; return (*this); }
			ra_iterator					operator--(int){ ra_iterator tmp = *this; ptr--; return (tmp); }

			ra_iterator					operator+(const difference_type diff) const { return (ra_iterator(ptr + diff)); }
			friend ra_iterator			operator+(const difference_type diff, ra_iterator& rhs) { return ra_iterator(rhs.ptr + diff);}
			ra_iterator					operator-(const difference_type diff) const { return (ra_iterator(ptr - diff)); }
			difference_type				operator-(const ra_iterator& rhs) const { return (this->base() - rhs.base()); }
	
			ra_iterator&				operator+=(const difference_type diff) { ptr+= diff; return (*this); }
			ra_iterator&				operator-=(const difference_type diff) { ptr-= diff; return (*this); }

			operator					random_access_iterator<const value_type> () const { return random_access_iterator<const value_type>(ptr); }

		protected:
			pointer	ptr;
	};

	// Operator overloads for different iterator types
	// (e.g. iterator - const_iterator)


	template <class U, class V>
	bool	operator==(random_access_iterator<U> it1, random_access_iterator<V> it2)
	{ return (it1.base() == it2.base()); }

	template <class U, class V>
	bool	operator!=(random_access_iterator<U> it1, random_access_iterator<V> it2)
	{ return (it1.base() != it2.base()); }

	template <class U, class V>
	bool	operator>=(random_access_iterator<U> it1, random_access_iterator<V> it2)
	{ return (it1.base() >= it2.base()); }

	template <class U, class V>
	bool	operator<=(random_access_iterator<U> it1, random_access_iterator<V> it2)
	{ return (it1.base() <= it2.base()); }

	template <class U, class V>
	bool	operator>(random_access_iterator<U> it1, random_access_iterator<V> it2)
	{ return (it1.base() > it2.base()); }

	template <class U, class V>
	bool	operator<(random_access_iterator<U> it1, random_access_iterator<V> it2)
	{ return (it1.base() < it2.base()); }
	
	template <class U, class V>
	typename random_access_iterator<U>::difference_type
	operator-(random_access_iterator<U> it1, random_access_iterator<V> it2)
	{ return (it1.base() - it2.base()); }


	// Reverse Iterator implementation

	template <class Iterator>
	class reverse_iterator
	{
		public:

		typedef	Iterator														iterator_type;
		typedef	typename iterator_traits<Iterator>::iterator_category			iterator_category;
		typedef	typename iterator_traits<Iterator>::value_type					value_type;
		typedef	typename iterator_traits<Iterator>::difference_type				difference_type;
		typedef	typename iterator_traits<Iterator>::pointer						pointer;
		typedef	typename iterator_traits<Iterator>::reference					reference;
		
		private:

		iterator_type	_base;

		public: 
		
		reverse_iterator(): _base(NULL)
		{}
		explicit reverse_iterator(iterator_type it): _base(it)
		{}
		template <class Iter>
		reverse_iterator(const reverse_iterator<Iter>& rev_it): _base(rev_it.base())
		{}
		~reverse_iterator()
		{}

		iterator_type			base() const { return (_base); }

		reference				operator*() const { return ( (--iterator_type(_base)).operator*()); }
		pointer					operator->() const { return (&(operator*())); }
		reference				operator[](difference_type n) const { return ( (--iterator_type(_base - n)).operator*()); }

		reverse_iterator		operator+(difference_type n) const { return (reverse_iterator(_base - n)); }
		reverse_iterator&		operator+=(difference_type n){_base -= n; return (*this); }
		reverse_iterator		operator-(difference_type n) const { return (reverse_iterator(_base + n)); }
		reverse_iterator&		operator-=(difference_type n){_base += n; return (*this); }

		reverse_iterator&		operator++() { --_base; return (*this); }
		reverse_iterator		operator++(int) { reverse_iterator tmp = *this; --_base; return (tmp); }
		reverse_iterator&		operator--() { ++_base; return (*this); }
		reverse_iterator		operator--(int) { reverse_iterator tmp = *this; ++_base; return (tmp); }

	};

	// Non member reverse_iterator functions

	template <class Iterator>
	bool	operator==(const reverse_iterator<Iterator>& lhs,
					   const reverse_iterator<Iterator>& rhs)
	{ return (lhs.base() == rhs.base()); }

	template <class U, class V>
	bool	operator==(const reverse_iterator<U>& lhs,
					   const reverse_iterator<V>& rhs)
	{ return (lhs.base() == rhs.base()); }


	template <class Iterator>
	bool	operator!=(const reverse_iterator<Iterator>& lhs,
					   const reverse_iterator<Iterator>& rhs)
	{ return (lhs.base() != rhs.base()); }
	
	template <class U, class V>
	bool	operator!=(const reverse_iterator<U>& lhs,
					   const reverse_iterator<V>& rhs)
	{ return (lhs.base() != rhs.base()); }


	template <class Iterator>
	bool	operator<(const reverse_iterator<Iterator>& lhs,
					   const reverse_iterator<Iterator>& rhs)
	{ return (lhs.base() > rhs.base()); }

	template <class U, class V>
	bool	operator<(const reverse_iterator<U>& lhs,
					   const reverse_iterator<V>& rhs)
	{ return (lhs.base() > rhs.base()); }

	
	template <class Iterator>
	bool	operator<=(const reverse_iterator<Iterator>& lhs,
					   const reverse_iterator<Iterator>& rhs)
	{ return (lhs.base() >= rhs.base()); }

	template <class U, class V>
	bool	operator<=(const reverse_iterator<U>& lhs,
					   const reverse_iterator<V>& rhs)
	{ return (lhs.base() >= rhs.base()); }

	
	template <class Iterator>
	bool	operator>(const reverse_iterator<Iterator>& lhs,
					   const reverse_iterator<Iterator>& rhs)
	{ return (lhs.base() < rhs.base()); }

	template <class U, class V>
	bool	operator>(const reverse_iterator<U>& lhs,
					   const reverse_iterator<V>& rhs)
	{ return (lhs.base() < rhs.base()); }

	
	template <class Iterator>
	bool	operator>=(const reverse_iterator<Iterator>& lhs,
					   const reverse_iterator<Iterator>& rhs)
	{ return (lhs.base() <= rhs.base()); }

	template <class U, class V>
	bool	operator>=(const reverse_iterator<U>& lhs,
					   const reverse_iterator<V>& rhs)
	{ return (lhs.base() <= rhs.base()); }
	

	template <class Iterator>
  	reverse_iterator<Iterator> operator+ (
             typename reverse_iterator<Iterator>::difference_type n,
             const reverse_iterator<Iterator>& rev_it)
	{ return (rev_it + n); }

	template <class Iterator>
 	typename reverse_iterator<Iterator>::difference_type operator- (
						const reverse_iterator<Iterator>& lhs,
						const reverse_iterator<Iterator>& rhs)
	{ return (rhs.base() - lhs.base()); }

	template <class U, class V>
 	typename reverse_iterator<V>::difference_type operator- (
						const reverse_iterator<U>& lhs,
						const reverse_iterator<V>& rhs)
	{ return (rhs.base() - lhs.base()); }


	//Bidirectional iterator for map

template <typename value_type, typename node_type>
class map_iterator : public ft::iterator<ft::bidirectional_iterator_tag, value_type>
{
	private:
		typedef	typename value_type::first_type									first_type;
		typedef	typename value_type::second_type								second_type;
		typedef	iterator<ft::bidirectional_iterator_tag, value_type>			parent;

	protected:
		node_type	*_node;
	public:
		typedef ptrdiff_t									difference_type;
		typedef value_type&									reference;
		typedef	value_type*									pointer;
		typedef	typename parent::iterator_category			iterator_category;

		map_iterator(void): _node(NULL) {}
		map_iterator(node_type *src): _node(src) {}
		map_iterator(const map_iterator &src){ *this = src; }
		~map_iterator()	{}
	
		map_iterator&	operator=(map_iterator const &rhs)
		{ this->_node = rhs._node; return (*this); }

		bool operator==(const map_iterator &rhs) const
		{ return (rhs._node == this->_node); }

		bool operator!=(const map_iterator &rhs) const
		{ return (rhs._node != this->_node); }

		map_iterator	&operator++(void){	_node = _node->successor(); return(*this);	}
		map_iterator	operator++(int)
		{
			map_iterator res(*this);
			++(*this);
			return (res);
		}
		map_iterator	&operator--(void){ _node = _node->predecessor(); return (*this); }
		map_iterator	operator--(int)
		{
			map_iterator res(*this);
			--(*this);
			return (res);
		}

		reference		operator*(void) const
		{ return (this->_node->data); }
		pointer			operator->(void) const
		{ return (&(this->_node->data));}

		first_type		first()
		{ return (this->_node->getKey()); }

		second_type 	second()
		{ return (this->_node->getValue()); }

		operator		map_iterator<const value_type, node_type>() const
		{ return map_iterator<const value_type, node_type>(this->_node); }

};

}
#endif