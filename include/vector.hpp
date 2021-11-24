/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bditte <bditte@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 10:58:17 by bditte            #+#    #+#             */
/*   Updated: 2021/11/24 14:37:58 by bditte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_HPP
# define VECTOR_HPP

# include <iostream>
# include <stdlib.h>
namespace ft 
{
    template <class T, class Alloc = std::allocator<T> > 
    class vector
    {
        public:

        typedef T                                   						value_type;
        typedef Alloc                               						allocator_type;
        typedef value_type&                         						reference;
        typedef const value_type&                   						const_reference;
        typedef typename Alloc::pointer             						pointer;
        typedef typename Alloc::const_pointer       						const_pointer;
        typedef std::size_t                         						size_type;
		typedef std::ptrdiff_t                      						difference_type;
        typedef	std::iterator<std::random_access_iterator_tag, T>			iterator;
		typedef	const std::iterator<std::random_access_iterator_tag, T>		const_iterator;
		typedef std::reverse_iterator<iterator>								reverse_iterator;
		typedef const std::reverse_iterator<const_iterator>						const_reverse_iterator;
	/*
		iterator 		begin() { vector::iterator res = this->_array; return (res); };
		const iterator	begin() const;*/
		/* Constructors */
        explicit vector(const allocator_type& alloc = allocator_type()): _array(NULL), _size(0), _capacity(0), _allocator(alloc) {};
        explicit vector(size_type n, const value_type& val = value_type(), const allocator_type& alloc = allocator_type()): _size(n), _capacity(n)
        {
			this->_allocator = alloc;
			this->_array = NULL;
			if (n == 0)
				return ;
            try 
            {
                this->_array = this->_allocator.allocate(n); 
            }
            catch (std::exception& e)
            {
                throw e;
            }
            for (size_type i = 0; i < n; i++)
                this->_allocator.construct(this->_array + i, val);  
        }
       /* template <class InputIterator, class = typename std::enable_if<std::is_integral<InputIterator>::value>::type>
        vector(InputIterator first, InputIterator last, const allocator_type& alloc = allocator_type())
        {
            InputIterator   begin = first;
            int             size = 0;
            
            while (begin++ != last)
                size++;
            this->_allocator = alloc;
            try 
            {
                this->_array = this->get_allocator().allocate(size); 
            }
            catch (std::exception& e)
            {
                throw e;
            }
            for (int i = 0; i < size; i++)
                this->get_allocator().construct(this->_array + i, first++);
            this->_size = size;
			this->_capacity = size;
        }*/
        vector(const vector& x)
        {
            this->_size = x.size();
            this->_allocator = x.get_allocator();
			this->_capacity = x.capacity();
			try 
            {
                this->_array = this->get_allocator().allocate(x.capacity()); 
            }
            catch (std::exception& e)
            {
                throw e;
            }
			for (size_type i = 0; i < this->_size; i++)
				this->_array[i] = x._array[i];
        }
		/* Destructor */
		~vector() { this->_allocator.deallocate(this->_array, this->_capacity); };
		/* Capacity */
        size_type	size(void) const { return (this->_size); };
		size_type 	max_size() const { return (this->get_allocator().max_size()); };
		void		resize(size_type n, value_type val = value_type())
		{
			T*	res;

			if (n <= this->_size)
				this->_size -= this->_size - n;
			else
			{
				try
				{
					res = this->_allocator.allocate(n);
					for (size_type i = 0; i < this->_size; i++)
                		this->get_allocator().construct(res + i, this->_array[i]);
					for (size_type i = this->_size; i < n; i++)
						res[i] = val;
					this->_allocator.deallocate(this->_array, this->capacity);
					this->_array = res;
					this->_size = n;
					this->_capacity = n;
				}
				catch (const std::exception& e)
				{
					throw e;
				}
			}
		}
		size_type	capacity(void) const { return (this->_capacity); };
		void		reserve(size_type n)
		{
			T*	res;

			if (n <= this->_capacity)
				return ;
			if (n > this->max_size())
				throw std::length_error("vector::reserve");
			try
			{
				res = this->_allocator.allocate(n);
				for (size_type i = 0; i < this->_size; i++)
					this->get_allocator().construct(res + i, this->_array[i]);
				this->_allocator.deallocate(this->_array, this->_capacity);
				this->_array = res;
				this->_capacity = n;
			}
			catch (const std::exception& e)
			{
				throw e;
			}
		}
		bool		empty(void)	const { if (this->_size == 0) {return (true);} return (false); };
		
		/* Element access */
		reference		operator[](size_type n) {return (this->_array[n]); };
		const_reference	operator[](size_type n) const { return (this->_array[n]); };
        /*
		* NEED TO ADD CORRECT MESSAGE
		*/
		reference		at(size_type n)
		{
			if (n > this->_size || !this->_size)
				throw std::out_of_range("std::at");
			return (this->_array[n]);
		}
		const_reference	at(size_type n) const
		{
			if (n > this->_size || !this->_size)
				throw std::out_of_range("std::at");
			return (this->_array[n]);
		}
		reference			front(void) { return (*this->_array); };
		const_reference		front(void) const { return (*this->_array); };
		reference			back(void) { return (this->_array[this->_size - 1]); };
		const_reference		back(void) const { return (this->_array[this->_size - 1]); };
		value_type*			data(void) { return (this->_array); };
		const value_type*	data(void) const { return (this->_array); };

		/* Modifiers */
		//template <class InputIterator>
  		//void assign (InputIterator first, InputIterator last);
		void assign (size_type n, const value_type& val)
		{
			if (n <= this->_capacity)
			{
				for (size_type i = 0; i < n; i++)
					this->_array[i] = val;
				this->_size = n;
			}
			else
			{
				T* res;
				try
				{
					res = this->_allocator.allocate(n);
					for (size_type i = 0; i < n; i++)
						this->get_allocator().construct(res + i, val);
					this->_allocator.deallocate(this->_array, this->_capacity);
					this->_array = res;
					this->_capacity = n;
					this->_size = n;
				}
				catch (const std::exception& e)
				{
					throw e;
				}
			}
		}
		/* Allocator */
		allocator_type get_allocator() const { return (this->_allocator); };

        private:
        
        T*					_array;
        size_type			_size;
        size_type			_capacity;
        allocator_type		_allocator;
    };
}

#endif