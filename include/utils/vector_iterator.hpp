/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iterator.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bditte <bditte@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/25 10:30:47 by bditte            #+#    #+#             */
/*   Updated: 2022/01/04 14:16:13 by bditte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ITERATOR_HPP
# define ITERATOR_HPP

template <class T>
class RandomIterator 
{
public:

	typedef	T					value_type;
	typedef T&					reference;
	typedef T*					pointer;
	typedef const T&			const_reference;
	typedef	std::ptrdiff_t		difference_type;

	RandomIterator(value_type* ptr = NULL): ptr(ptr){}
	RandomIterator(const RandomIterator& it): ptr(it.get_ptr()){}
	virtual ~RandomIterator(){}

	RandomIterator&							operator=(RandomIterator<value_type> const& src){this->ptr = src.ptr; return *this;}
	RandomIterator&							operator=(value_type* ptr){this->ptr = ptr; return *this;};
	
	bool									operator==(const RandomIterator<value_type> param) const { return (param.ptr == this->ptr);}
	bool									operator!=(const RandomIterator<value_type> param) const { return (param.ptr != this->ptr);}
	bool									operator<(const RandomIterator<value_type> param) const { return (this->ptr < param.ptr);}
	bool									operator<=(const RandomIterator<value_type> param) const { return (this->ptr <= param.ptr);}
	bool									operator>(const RandomIterator<value_type> param) const { return (this->ptr > param.ptr);}
	bool									operator>=(const RandomIterator<value_type> param) const { return (this->ptr >= param.ptr);}

	RandomIterator<value_type>&				operator++(){ this->ptr++; return *this;}
	RandomIterator<value_type>				operator++(int){RandomIterator<value_type> tmp = *this; this->ptr++; return tmp;}	
	RandomIterator<value_type>&				operator--(){ this->ptr--; return *this;}
	RandomIterator<value_type>				operator--(int){RandomIterator<value_type> tmp = *this; this->ptr--; return tmp;}
	
	RandomIterator<value_type>				operator+(const difference_type& diff){	return (RandomIterator<value_type>(this->ptr + diff)); }
	friend RandomIterator<value_type>		operator+(const difference_type& diff, RandomIterator<value_type>& rhs) { return rhs.operator+(diff); }
	RandomIterator<value_type>				operator-(const difference_type& diff){	return (RandomIterator<value_type>(this->ptr - diff)); }
	difference_type							operator-(const RandomIterator<value_type>& rhs) const { return (std::distance(rhs.get_ptr(), this->get_ptr()));}
	

protected:
		
	value_type*					get_ptr() const { return (this->ptr); };
	void						set_ptr(value_type* ptr) { this->ptr = ptr; };
	

	value_type*		ptr;	
};

template <class T>
class vector_iterator: public RandomIterator<T>
{

	protected:
		vector_iterator(T* ptr): parent(ptr){}
	private:
		vector_iterator(const RandomIterator<T> src) : RandomIterator<T>(src) {}
	public:

		typedef	T					value_type;
		typedef T&					reference;
		typedef T*					pointer;
		typedef const T&			const_reference;
		typedef	std::ptrdiff_t		difference_type;
		typedef	RandomIterator<T>	parent;

		vector_iterator(): parent(NULL){}
		vector_iterator(const vector_iterator& it): parent(it){}
		~vector_iterator(){}

		vector_iterator&			operator+=(const difference_type& diff){ parent::ptr += diff; return *this;}
		vector_iterator&			operator-=(const difference_type& diff){ parent::ptr -= diff; return *this;}
		vector_iterator&			operator++(){ parent::ptr++; return *this;}
		vector_iterator&			operator--(){ parent::ptr--; return *this;}
		vector_iterator				operator++(int){vector_iterator tmp = *this; parent::ptr++; return tmp;}
		vector_iterator				operator--(int){vector_iterator tmp = *this; parent::ptr--; return tmp;}
		
		vector_iterator				operator+(const difference_type& diff) const	{ return vector_iterator(parent::ptr + diff); }
		friend vector_iterator		operator+(const difference_type& diff, vector_iterator& rhs) { return rhs.operator+(diff); }
		vector_iterator				operator-(const difference_type& diff) const { return vector_iterator(parent::ptr - diff);}		
		difference_type				operator-(const vector_iterator& rhs) const { return (std::distance(rhs.get_ptr(), this->get_ptr()));}

		reference					operator*(){ return (*parent::ptr); }
		pointer						operator->() const { return (parent::ptr); }
		reference					operator[](int n) const { return (this->ptr[n]); }
	
};

namespace ft 
{
	template <class Iterator>
	class reverse_iterator
	{
		public:

			typedef Iterator							iterator_type;
			typedef typename iterator_type::difference_type		difference_type;
			typedef typename iterator_type::reference			reference;
			typedef typename iterator_type::pointer				pointer;

			reverse_iterator(void): _base() {}
			explicit reverse_iterator(iterator_type it): _base(it) {}
			template <class Iter> reverse_iterator(const reverse_iterator<Iter>& rev_it): _base(rev_it.base()) {}
			template <class Iter> reverse_iterator &operator=(const reverse_iterator<Iter>& rev_it) { this->_base = rev_it.base(); return (*this); }
			
			iterator_type 		base(void) const { return this->_base; };

			reference			operator*(void) const { return (--Iterator(this->_base)).operator*(); };
			pointer				operator->(void) const { return &this->operator*(); };

			reverse_iterator	&operator++(void) { this->_base.operator--(); return *this; };
			reverse_iterator	operator++(int) { return reverse_iterator(this->_base.operator--(0)); };
			reverse_iterator	&operator--(void) { this->_base.operator++(); return *this; };
			reverse_iterator	operator--(int) { return reverse_iterator(this->_base.operator++(0)); };
			
			template <class Iter>
			difference_type		operator-(const reverse_iterator<Iter> &src) { return src.base().operator-(this->_base); };
		
			reverse_iterator	operator+(difference_type n) const { return reverse_iterator(this->_base.operator-(n)); };
			reverse_iterator	&operator+=(difference_type n) { this->_base.operator-=(n); return *this; };
			reverse_iterator	operator- (difference_type n) const { return reverse_iterator(this->_base.operator+(n)); };
			reverse_iterator	&operator-=(difference_type n) { this->_base.operator+=(n); return *this; };
			reference			operator[](difference_type n) const { return *this->operator+(n); };

			friend reverse_iterator	operator+(difference_type n, const reverse_iterator &rhs)
				{ return rhs.operator+(n); };

			template <class U> bool	operator==(const reverse_iterator<U> &rhs) const { return this->_base.operator==(rhs.base()); };
			template <class U> bool	operator!=(const reverse_iterator<U> &rhs) const { return this->_base.operator!=(rhs.base()); };
			template <class U> bool	operator< (const reverse_iterator<U> &rhs) const { return this->_base.operator> (rhs.base()); };
			template <class U> bool	operator<=(const reverse_iterator<U> &rhs) const { return this->_base.operator>=(rhs.base()); };
			template <class U> bool	operator> (const reverse_iterator<U> &rhs) const { return this->_base.operator< (rhs.base()); };
			template <class U> bool	operator>=(const reverse_iterator<U> &rhs) const { return this->_base.operator<=(rhs.base()); };
		
		protected:

		Iterator	_base;


	};
}


#endif