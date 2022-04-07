/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bditte <bditte@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 10:58:17 by bditte            #+#    #+#             */
/*   Updated: 2022/04/07 11:33:04 by bditte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_HPP
# define VECTOR_HPP

# include "utils/utils.hpp"
# include "utils/iterator.hpp"
namespace ft
{
    template <class T, class Allocator = std::allocator<T> > 
    class vector
    {
        public:

		// Member types

        typedef T                                   						value_type;
        typedef Allocator                               					allocator_type;
        typedef value_type&                         						reference;
        typedef const value_type&                   						const_reference;
        typedef typename Allocator::pointer             					pointer;
        typedef typename Allocator::const_pointer       					const_pointer;
        typedef std::size_t                         						size_type;
		typedef std::ptrdiff_t                      						difference_type;
        typedef	ft::random_access_iterator<value_type>						iterator;
		typedef	ft::random_access_iterator<const value_type>				const_iterator;
		typedef ft::reverse_iterator<iterator>								reverse_iterator;
		typedef ft::reverse_iterator<const_iterator>						const_reverse_iterator;
	

		iterator 										begin() { return (iterator(this->_array)); }
		const_iterator									begin() const { return (const_iterator(this->_array)); }
		iterator 										end() { return (iterator(&this->_array[this->_size])); }
		const_iterator									end() const { return (const_iterator(&this->_array[this->_size])); }
		reverse_iterator 								rbegin() { return (reverse_iterator(&this->_array[this->_size])); }
		const_reverse_iterator							rbegin() const { return (const_reverse_iterator(&this->_array[this->_size])); }
		reverse_iterator 								rend() { return (reverse_iterator(this->_array)); }
		const_reverse_iterator							rend() const { return (const_reverse_iterator(this->_array)); }
		
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
		template <class InputIterator>
		vector (typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type first,
				InputIterator last,
				const allocator_type& alloc = allocator_type())
       	{
            InputIterator	begin = first;
            int             size = 0;
            
            while (begin++ != last)
                size++;
            this->_allocator = alloc;
            try 
            {
                this->_array = this->_allocator.allocate(size); 
            }
            catch (std::exception& e)
            {
                throw e;
            }
            for (int i = 0; i < size; i++)
                this->_allocator.construct(this->_array + i, *(first++));
            this->_size = size;
			this->_capacity = size;
        }
        vector(const vector& x)
        {
            this->_size = x.size();
            this->_allocator = x._allocator;
			this->_capacity = this->_size;
			try 
            {
				if (this->_size)
                	this->_array = this->_allocator.allocate(this->_size); 
            }
            catch (std::exception& e)
            {
                throw e;
            }
			for (size_type i = 0; i < this->_size; i++)
				this->_allocator.construct(&this->_array[i], x._array[i]);
        }
		
		/* Destructor */
		~vector() 
		{
			if (this->_capacity)
			{
				this->destroy_objects();
				this->_allocator.deallocate(this->_array, this->_capacity);
			}
		};
		
		vector&		operator=(const vector& rhs)
		{
			if (this->_array == rhs._array)
				return (*this);
			if (this->_capacity)
				this->destroy_objects();
			this->_size = 0;
			this->assign(rhs.begin(), rhs.end());
			return (*this);
		}

		/* Capacity */
        size_type	size(void) const { return (this->_size); };
		size_type 	max_size() const { return (this->_allocator.max_size()); };
		void		resize(size_type n, value_type val = value_type())
		{
			if (n <= this->_size)
			{
				while (n < this->_size)
					this->_allocator.destroy(&this->_array[--this->_size]);
			}
			else
			{
				if (n > this->_capacity)
				{
					try
					{	
						if (n < this->_capacity * 2)	
							this->reserve(this->_capacity * 2);
						else
							this->reserve(n);
					}
					catch(const std::exception& e)
					{
						throw std::length_error("vector::_M_fill_insert");
					}
				}
				for (size_type i = this->_size; i < n; i++)
					this->_allocator.construct(&(this->_array[i]), val);
				this->_size = n;
			}
		}
		size_type	capacity(void) const { return (this->_capacity); };
		void		reserve(size_type n)
		{
			value_type*	res;

			if (n <= this->_capacity)
				return ;
			if (n > this->max_size())
				throw std::length_error("vector::reserve");
			try
			{
				res = this->_allocator.allocate(n);
				this->_capacity = n;
			}
			catch (const std::exception& e)
			{
				throw e;
			}
			for (size_type i = 0; i < this->_size; i++)
				this->_allocator.construct(res + i, this->_array[i]);
			this->destroy_objects();
			this->_allocator.deallocate(this->_array, this->_capacity);
			this->_array = res;
		}
		bool		empty(void)	const 
		{ 
			if (this->_size == 0) 
				return (true);
			return (false); 
		}
		
		/* Element access */
		reference		operator[](size_type n) {return (this->_array[n]); };
		const_reference	operator[](size_type n) const { return (this->_array[n]); };
		reference		at(size_type n)
		{
			if (n > this->_size || !this->_size)
			{
				std::string	msg("vector::_M_range_check: __n (which is ");
				msg += int_to_str(n);
				msg += std::string(") >= this->size() (which is ");
				msg += int_to_str(this->_size);
				msg += std::string(")");
				throw std::out_of_range(msg);
			}
			return (this->_array[n]);
		}
		const_reference	at(size_type n) const
		{
			
			if (n > this->_size || !this->_size)
			{
				std::string	msg("vector::_M_range_check: __n (which is ");
				msg += int_to_str(n);
				msg += std::string(") >= this->size() (which is ");
				msg += int_to_str(this->_size);
				msg += std::string(")");
				throw std::out_of_range(msg);
			}
			return (this->_array[n]);
		}
		reference			front(void) { return (*this->_array); };
		const_reference		front(void) const { return (*this->_array); };
		reference			back(void) { return (this->_array[this->_size - 1]); };
		const_reference		back(void) const { return (this->_array[this->_size - 1]); };
		value_type*			data(void) { return (this->_array); };
		const value_type*	data(void) const { return (this->_array); };

		/* Modifiers */
		template <class InputIterator>
  		void				assign (typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type first,
		  							InputIterator last)
		{
			InputIterator	tmp = first;
			size_type		size = 0;
		
			while (tmp != last)
			{
				tmp++;
				size++;
			}
			if (!size)
			{
				clear();
				if (this->_capacity)
					this->_allocator.deallocate(this->_array, this->_capacity),
				this->_array = NULL;
				_capacity = 0;	
			}
			size_type i = 0;
			while (i < this->_capacity && first != last)
			{
				this->_allocator.construct(&this->_array[i++], *first++);
			}
			if (size > this->_capacity)
			{
				value_type* res;
				size_type 	new_capacity = 0;
				try
				{
					if (this->_capacity * 2 > size)
					{
						res = this->_allocator.allocate(this->_capacity * 2);
						new_capacity = this->_capacity * 2;
					}
					else
					{
						res = this->_allocator.allocate(size);
						new_capacity = size;
					}
					for (size_type j = 0; j < size; j++)
					{
						if (j < i)
						{
							this->_allocator.construct(res + j, this->_array[j]);
						}
						else
						{
							this->_allocator.construct(res + j, *first++);
						}
					}
					this->destroy_objects();
					if (this->_capacity)
						this->_allocator.deallocate(this->_array, this->_capacity);
					this->_capacity = new_capacity;
					this->_array = res;
				}
				catch (const std::exception& e)
				{
					throw e;
				}
			}
			this->_size = size;
		}
		void 				assign (size_type n, const value_type& val)
		{
			if (n <= this->_capacity)
			{
				for (size_type i = 0; i < n; i++)
					this->_allocator.construct(&this->_array[i], val);
				this->_size = n;
			}
			else
			{
				value_type* res;
				try
				{
					res = this->_allocator.allocate(n);
				}
				catch (const std::exception& e)
				{
					throw e;
				}
				for (size_type i = 0; i < n; i++)
					this->_allocator.construct(res + i, val);
				this->_allocator.deallocate(this->_array, this->_capacity);
				this->_array = res;
				this->_capacity = n;
				this->_size = n;
			}
		}
		void				push_back(const value_type&	val)
		{
			if (!this->_capacity)
			{
				try
				{
					this->_array = this->_allocator.allocate(1);
				}
				catch(const std::exception& e)
				{
					throw e;
				}
				this->_allocator.construct(this->_array, val);
				this->_capacity++;
				this->_size++;
				return ;
			}
			if (this->_size == this->_capacity)
				this->reserve(this->_size * 2);
			this->_allocator.construct(&this->_array[this->_size], val);
			this->_size++;
		}
		void				pop_back()
		{
			if (!this->_size)
				return ;
			this->_allocator.destroy(&this->_array[this->_size - 1]);
			this->_size--;
		}iterator			insert(iterator position, const value_type& val)
		{
			difference_type		diff = position - begin();

			insert(position, 1, val);
			return (iterator(begin() + diff));
		}
		
		void				insert(iterator position, size_type n, const value_type& val)
		{
			if (n == 0)
				return ;
			difference_type diff = position - begin();

			this->resize(this->_size + n, val);

			iterator end = this->end();
			position = begin() + diff;
			iterator last_val = begin() + (this->_size - n);
			
			while (last_val != position)
			{
				--end;
				this->_allocator.destroy(end.base());
				this->_allocator.construct(end.base(), *--last_val);
			}
			while (n-- > 0)
			{
				this->_allocator.destroy(position.base());
				this->_allocator.construct(position.base(), val);
				position++;
			}
		}
		
		template <class InputIterator>
    	void insert (iterator position,
					typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type first,
					InputIterator last)
		{
			difference_type diff = position - begin();
			size_type 		size = 0;

			for (InputIterator it = first; it != last; it++)
				size++;
			this->resize(this->_size + size, *first);

			iterator end = this->end();
			position = begin() + diff;
			iterator last_val = begin() + (this->_size - size);
			
			while (last_val != position)
			{
				--end;
				this->_allocator.destroy(end.base());
				this->_allocator.construct(end.base(), *--last_val);
			}
			while (first != last)
			{
				this->_allocator.destroy(position.base());
				this->_allocator.construct(position.base(), *first++);
				position++;
			}
		}
		
		
		iterator 			erase(iterator position)
		{
			return (this->erase(position, position + 1));
		}
		iterator			erase(iterator first, iterator last)
		{
			iterator	pos = first;
			iterator	end = this->end();
			size_type	size = 0;

			while (pos != last)
			{
				pos++;
				size++;
			}
			pos = first;
			while (last != end)
			{
				*first = *last;
				++first;
				++last;
			}
			while (size-- > 0)
				this->_allocator.destroy(&this->_array[--this->_size]);
			return (pos);
		}

		void			swap(vector& x)
		{
			value_type* 		tmp_array = this->_array;
			size_type			tmp_size = this->_size;
       		size_type			tmp_capacity = this->_capacity;
        	allocator_type		tmp_allocator = this->_allocator;
			
			this->_array = x._array;
			this->_size = x._size;
			this->_capacity = x._capacity;
			this->_allocator = x._allocator;
			x._array = tmp_array;
			x._size = tmp_size;
			x._capacity = tmp_capacity;
			x._allocator = tmp_allocator;

			return ;
		}

		void			clear() { this->destroy_objects(); this->_size = 0; }
		/* Allocator */
		allocator_type get_allocator() const { return (this->_allocator); };

        private:
        
        T*					_array;
        size_type			_size;
        size_type			_capacity;
        allocator_type		_allocator;

		std::string	int_to_str(const int n) const
		{
			std::stringstream ss;
			ss << n;
			return (ss.str());
		}

		void		destroy_objects()
		{
			for (size_type i = 0; i < this->_size; i++)
				this->_allocator.destroy(this->_array + i);
		}

    };

	template <class T, class Alloc>
	bool		operator== (const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs)
	{
		if (lhs.size() != rhs.size())
			return (false);
		return (ft::equal(lhs.begin(), lhs.end(), rhs.begin()));
	}

	template <class T, class Alloc>
	bool		operator!= (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
	{
		return (!(lhs == rhs));
	}

	template <class T, class Alloc>
	bool		operator<  (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
	{
		typename vector<T, Alloc>::size_type i;
		for (i = 0; i < lhs.size(); i++)
		{
			if (i == rhs.size())
				return (false);
			if (lhs[i] < rhs[i])
				return (true);
			if (lhs[i] > rhs[i])
				return (false);
		}
		if (i < rhs.size())
			return (true);
		return (false);
	}

	template <class T, class Alloc>
	bool operator<= (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
	{
		return (!(rhs < lhs));
	}

	template <class T, class Alloc>
	bool operator>  (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
	{
		return (rhs < lhs);
	}

	template <class T, class Alloc>
	bool operator>= (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
	{
		return (!(lhs < rhs));
	}

	template <class T, class Alloc>
  	void swap (vector<T,Alloc>& x, vector<T,Alloc>& y)
	{
		x.swap(y);
	}

}

#endif