/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iterator.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bditte <bditte@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/25 10:30:47 by bditte            #+#    #+#             */
/*   Updated: 2021/12/15 12:06:20 by bditte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ITERATOR_HPP
# define ITERATOR_HPP

template <class T>
class myIterator 
{
public:

	typedef	T					value_type;
	typedef T&					reference;
	typedef T*					pointer;
	typedef const T&			const_reference;
	typedef	std::ptrdiff_t		difference_type;

	myIterator(value_type* ptr = NULL): ptr(ptr){}
	myIterator(const myIterator<value_type>& it): ptr(it.get_ptr()){}
	~myIterator(){}

	myIterator&					operator=(const myIterator<value_type>& src){this->ptr = src.ptr; return *this;}
	myIterator&					operator=(value_type* ptr){this->ptr = ptr; return *this;};
	
	bool						operator==(const myIterator<value_type> param) const { return (param.ptr == this->ptr);}
	bool						operator!=(const myIterator<value_type> param) const { return (param.ptr != this->ptr);}

	myIterator<value_type>&		operator+=(const difference_type& diff){ this->ptr += diff; return *this;}
	myIterator<value_type>&		operator-=(const difference_type& diff){ this->ptr -= diff; return *this;}
	myIterator<value_type>&		operator++(){ this->ptr++; return *this;}
	myIterator<value_type>&		operator--(){ this->ptr--; return *this;}
	myIterator<value_type>		operator++(int){myIterator<value_type> tmp = *this; this->ptr++; return tmp;}
	myIterator<value_type>		operator--(int){myIterator<value_type> tmp = *this; this->ptr--; return tmp;}
	myIterator<value_type>		operator+(const difference_type& diff)
	{
		value_type *tmp_ptr = this->ptr; this->ptr += diff;
		myIterator<value_type> res = *this;
		this->ptr = tmp_ptr; return res;
	}
	myIterator<value_type>		operator-(const difference_type& diff)
	{
		value_type *tmp_ptr = this->ptr; this->ptr -= diff;
		myIterator<value_type> res = *this;
		this->ptr = tmp_ptr; return res;
	}
	
	value_type&		operator[](int n) const { return (this->ptr[n]); }

	difference_type				operator-(const myIterator<value_type>& rhs) const { return (std::distance(rhs.get_ptr(), this->get_ptr()));}

	reference					operator*(){ return (*this->ptr); }
	reference					operator->(){ return (*this->ptr); }
	const_reference				operator*() const { return (*this->ptr); }
	
	value_type*					get_ptr() const { return (this->ptr); };
	void						set_ptr(value_type* ptr) { this->ptr = ptr; };
	
protected:

	value_type*		ptr;	
};

template <class T>
class myReverseIterator : public myIterator<T>
{
public:

	typedef	T					value_type;
	typedef T&					reference;
	typedef const T&			const_reference;
	typedef	std::ptrdiff_t		difference_type;

	myReverseIterator(value_type* ptr = NULL): myIterator<value_type>(ptr){}
	myReverseIterator(const myIterator<value_type>& src): myIterator<value_type>(src.ptr){}
	myReverseIterator(const myReverseIterator<value_type>& src): myIterator<value_type>(src.ptr){}
	~myReverseIterator(){}

	myReverseIterator<value_type>&		operator=(myReverseIterator<value_type>& rhs){ this->set_ptr(rhs.get_ptr); return (*this); }
	myReverseIterator<value_type>&		operator=(myIterator<value_type>& rhs){ this->set_ptr(rhs.get_ptr); return (*this); }
	myReverseIterator<value_type>&		operator=(value_type* ptr){ this->set_ptr(ptr); return (*this); }

	myReverseIterator<value_type>&		operator+=(const difference_type diff){ this->ptr -= diff; return (*this); }
	myReverseIterator<value_type>&		operator-=(const difference_type diff){ this->ptr += diff; return (*this); }
	myReverseIterator<value_type>&		operator++(){ this->ptr--; return (*this); }
	myReverseIterator<value_type>&		operator--(){ this->ptr++; return (*this); }
	myReverseIterator<value_type>		operator++(int){ myReverseIterator<value_type> res = *this; this->ptr--; return (res); }
	myReverseIterator<value_type>		operator--(int){ myReverseIterator<value_type> res = *this; this->ptr++; return (res); }
	myReverseIterator<value_type>		operator+(const difference_type diff)
	{
		value_type *tmp = this->ptr;
		this->ptr -= diff;
		myReverseIterator<value_type> res = *this;
		this->ptr = tmp;
		return (res);
	}
	myReverseIterator<value_type>		operator-(const difference_type diff)
	{
		value_type *tmp = this->ptr;
		this->ptr += diff;
		myReverseIterator<value_type> res = *this;
		this->ptr = tmp;
		return (res);
	}

	difference_type						operator-(const myReverseIterator<value_type> rhs) const { return (std::distance(this->get_ptr(), rhs.get_ptr())); }

};

#endif