/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bditte <bditte@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 10:58:17 by bditte            #+#    #+#             */
/*   Updated: 2021/11/23 15:44:14 by bditte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_HPP
# define VECTOR_HPP

# include <iostream>

namespace ft 
{
    template <class T, class Alloc = std::allocator<T> > 
    class vector
    {
        public:

        typedef T                                   value_type;
        typedef Alloc                               allocator_type;
        typedef value_type&                         reference;
        typedef const value_type&                   const_reference;
        typedef typename Alloc::pointer             pointer;
        typedef typename Alloc::const_pointer       const_pointer;
        typedef std::size_t                         size_type;
        typedef std::ptrdiff_t                      difference_type;
        /*  
        * Need to add iterator typedefs
        */
        explicit vector(const allocator_type& alloc = allocator_type()): _size(0)
        {
            this->_allocator = alloc;
            try 
            { 
                this->_array = this->get_allocator().allocate(0); 
            }
            catch (std::exception& e)
            {
                throw e;
            }
        }
        explicit vector(size_type n, const value_type& val = value_type(), const allocator_type& alloc = allocator_type()): _size(n)
        {
            this->_allocator = alloc;
            try 
            {
                this->_array = this->get_allocator().allocate(n); 
            }
            catch (std::exception& e)
            {
                throw e;
            }
            for (size_type i = 0; i < n; i++)
                this->get_allocator().construct(this->_array + i, val);       
        }
        template <class InputIterator, class = typename std::enable_if<std::is_integral<InputIterator>::value>::type>
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
        }
        size_t size(void) const { return (this->_size); };

        allocator_type get_allocator() const { return (this->_allocator); };

        private:
        
        T*              _array;
        size_t          _size;
        allocator_type  _allocator;
    };
}

#endif