/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   const_iterator.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bditte <bditte@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/14 11:11:53 by bditte            #+#    #+#             */
/*   Updated: 2021/12/14 11:20:26 by bditte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONST_ITERATOR_HPP
# define CONST_ITERATOR_HPP

template <class T>
class myConstIterator 
{
	public:

		typedef	const T					value_type;
		typedef T&					reference;
		typedef const T&			const_reference;
		typedef	std::ptrdiff_t		difference_type;

		myConstIterator(value_type* ptr = NULL): ptr(ptr){}
		myConstIterator(const myConstIterator<value_type>& it): ptr(it.get_ptr()){}
		~myConstIterator(){}

		//myConstIterator<value_type>&		operator=()
		myConstIterator&					operator=(myConstIterator<value_type>& src){this->ptr = src.ptr; return *this;}
		myConstIterator&					operator=(value_type* ptr){this->ptr = ptr; return *this;};
		
		bool						operator==(const myConstIterator<value_type> param) const { return (param.ptr == this->ptr);}
		bool						operator!=(const myConstIterator<value_type> param) const { return (param.ptr != this->ptr);}

		myConstIterator<value_type>&		operator+=(const difference_type& diff){ this->ptr += diff; return *this;}
		myConstIterator<value_type>&		operator-=(const difference_type& diff){ this->ptr -= diff; return *this;}
		myConstIterator<value_type>&		operator++(){ this->ptr++; return *this;}
		myConstIterator<value_type>&		operator--(){ this->ptr--; return *this;}
		myConstIterator<value_type>		operator++(int){myConstIterator<value_type> tmp = *this; this->ptr++; return tmp;}
		myConstIterator<value_type>		operator--(int){myConstIterator<value_type> tmp = *this; this->ptr--; return tmp;}
		myConstIterator<value_type>		operator+(const difference_type& diff)
		{
			value_type *tmp_ptr = this->ptr; this->ptr += diff;
			myConstIterator<value_type> res = *this;
			this->ptr = tmp_ptr; return res;
		}
		myConstIterator<value_type>		operator-(const difference_type& diff)
		{
			value_type *tmp_ptr = this->ptr; this->ptr -= diff;
			myConstIterator<value_type> res = *this;
			this->ptr = tmp_ptr; return res;
		}
		
		difference_type				operator-(const myConstIterator<value_type>& rhs) const { return (std::distance(rhs.get_ptr(), this->get_ptr()));}

		reference					operator*(){ return (*this->ptr); }
		const_reference				operator*() const { return (*this->ptr); }
		
		value_type*					get_ptr() const { return (this->ptr); };
		void						set_ptr(value_type* ptr) { this->ptr = ptr; };
		
	protected:

		value_type*		ptr;	
};

#endif