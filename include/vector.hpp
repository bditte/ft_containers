/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bditte <bditte@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 10:58:17 by bditte            #+#    #+#             */
/*   Updated: 2021/12/01 14:54:33 by bditte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_HPP
# define VECTOR_HPP

# include <iostream>
# include <iterator.hpp>
namespace ft 
{

    template <class T, class Alloc = std::allocator<T> > 
    class vector
    {
        public:

		/* Member types */
        typedef T                                   						value_type;
        typedef Alloc                               						allocator_type;
        typedef value_type&                         						reference;
        typedef const value_type&                   						const_reference;
        typedef typename Alloc::pointer             						pointer;
        typedef typename Alloc::const_pointer       						const_pointer;
        typedef std::size_t                         						size_type;
		typedef std::ptrdiff_t                      						difference_type;
        typedef	myIterator<T>												iterator;
		typedef	myIterator<const T>											const_iterator;
		typedef myReverseIterator<T>										reverse_iterator;
		typedef const myReverseIterator<T>									const_reverse_iterator;
	
		/* Iterators */
		iterator 										begin() { return (iterator(this->_array)); }
		const_iterator									begin() const { return (const_iterator(this->_array)); }
		iterator 										end() { return (iterator(&this->_array[this->_size])); }
		const_iterator									end() const { return (const_iterator(&this->_array[this->_size])); }
		reverse_iterator 								rbegin() { return (reverse_iterator(&this->_array[this->_size - 1])); }
		const_reverse_iterator							rbegin() const { return (reverse_iterator(&this->_array[this->_size - 1])); }
		reverse_iterator 								rend() { return (reverse_iterator(this->_array - 1)); }
		const_reverse_iterator							rend() const { return (reverse_iterator(this->_array - 1)); }
		
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
			if (n <= this->_size)
				this->_size -= this->_size - n;
			else
			{
				value_type*	res;
				try
				{
					res = this->_allocator.allocate(this->_capacity * 2);
				}
				catch (const std::exception& e)
				{
					throw e;
				}
				for (size_type i = 0; i < this->_size; i++)
					this->get_allocator().construct(res + i, this->_array[i]);
				for (size_type i = this->_size; i < n; i++)
					res[i] = val;
				this->_allocator.deallocate(this->_array, this->_capacity);
				this->_array = res;
				this->_size = n;
				this->_capacity *= 2;
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
		/*template <class InputIterator>
  		void				assign (InputIterator first, InputIterator last)
		{
			InputIterator	tmp = first;
			size_type		size = 0;

			while (tmp != last)
				size++;
			size_type i = 0;
			while (i < this->_capacity && first != last)
			{
				this->_array[i++] = *first;
				first++;
			}
			if (size > this->_capacity)
			{
				value_type* res;
				try
				{
					res = this->_allocator.allocate(this->_capacity * 2);
					for (size_type j = 0; j < size; j++)
					{
						if (j < i)
							this->get_allocator().construct(res + j, this->_array[i]);
						else
						{
							this->get_allocator().construct(res + j, *first);
							first++;
						}
					}
					this->_allocator.deallocate(this->_array, this->_capacity);
					this->_array = res;
					this->_capacity *= 2;
				}
				catch (const std::exception& e)
				{
					throw e;
				}
			}
			this->_size = size;
		}*/
		void 				assign (size_type n, const value_type& val)
		{
			if (n <= this->_capacity)
			{
				for (size_type i = 0; i < n; i++)
					this->_array[i] = val;
				this->_size = n;
			}
			else
			{
				value_type* res;
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
		void				push_back(const value_type&	val)
		{
			if (this->_size == this->_capacity)
			{
				value_type* res;
				try
				{
					res = this->_allocator.allocate(this->_capacity * 2);
				}
				catch(const std::exception& e)
				{
					throw e;
				}
				for (size_type i = 0; i < this->_size; i++)
					res[i] = this->_array[i];
				this->_allocator.deallocate(this->_array, this->_capacity);
				this->_array = res;
				this->_capacity *= 2;
			}
			this->_array[this->_size] = val;
			this->_size++;
		}
		void				pop_back() { this->_size--; }
		iterator			insert(iterator position, const value_type& val)
		{
			if (this->_size == this->_capacity)
			{
				size_type	pos = 0;
				for (iterator i = this->begin(); i != position; i++)
				{
					pos++;
					if (i == this->end())
					{
						*position = val;
						pos = this->_size + 2;
					}
				}
				value_type* res;
				try
				{
					res = this->_allocator.allocate(this->_capacity * 2);
				}
				catch(const std::exception& e)
				{
					throw e;
				}
				int j = 0;
				for (size_type i = 0; i <= this->_size; i++)
				{
					if (i == pos)
						res[i] = val;
					else
						res[i] = this->_array[j++];
				}
				this->_allocator.deallocate(this->_array, this->_capacity);
				this->_array = res;
				this->_capacity *= 2;;
				this->_size++;
				if (pos > this->_size)
					return (position);
				return (iterator(this->_array + pos));
			}
			else
			{
				for (size_type i = 0; i <= this->_size; i++)
				{
					if (iterator(this->_array + i) == position)
					{
						value_type	next = this->_array[i];
						value_type 	tmp;
						this->_array[i] = val;
						i++;
						while (i <= this->_size)
						{
							tmp = next;
							next = this->_array[i];
							this->_array[i] = tmp;
							i++;
						}
						this->_size++;
						return (position);
					}
				}
			}
			return position;
		}
		/*void				insert(iterator position, size_type n, const value_type& val)
		{
			if (this->_size + n > this->_capacity)
			{
				value_type*	res;
				try
				{
					if (this->_capacity * 2 >= this->_capacity + n)
					{
						res = this->_allocator.allocate(this->_capacity * 2);
						this->_capacity *= 2;
					}
					else
					{
						res = this->_allocator.allocate(this->_capacity + n);
						this->_capacity += n;
					}
				}
				catch(const std::exception& e)
				{
					std::cerr << e.what() << '\n';
				}
				size_type	pos = 0;
				for (iterator i = this->begin(); i != position; i++)
				{
					pos++;
					if (i == this->end())
					{
						*position = val;
						pos = this->_size + 2;
						break ;
					}
				}
				int j = 0;
				size_type	added = 0;
				for (size_type i = 0; i <= this->_size + n; i++)
				{
					if (i >= pos && added < n)
					{
						res[i] = val;
						added++;
					}
					else
						res[i] = this->_array[j++];
				}
				this->_allocator.deallocate(this->_array, this->_capacity);
				this->_array = res;
				this->_size += n;
				if (pos > this->_size)
					return ;
				return ;								
			}
			for (size_type i = 0; i <= this->_size; i++)
				{
					if (iterator(this->_array + i) == position)
					{
						value_type	next = this->_array[i];
						value_type 	tmp;
						this->_array[i] = val;
						i++;
						while (i <= this->_size)
						{
							tmp = next;
							next = this->_array[i];
							this->_array[i] = tmp;
							i++;
						}
						this->_size++;
						return (position);
					}
				}
			iterator tmp = position;
			while (tmp != end())
			{
				*(tmp + n) = *tmp;
				tmp++;
			}		
		}*/

		iterator 			erase(iterator position)
		{
			*position = *(position + 1);
			position++;
			while (position != this->end())
			{
				*position = *(position + 1);
				position++;
			}
			this->_size--;
			return (position);
		}
		iterator			erase(iterator first, iterator last)
		{
			iterator	pos = first;
			size_type	size = 0;

			while (pos != last)
			{
				pos++;
				size++;
			}
			pos = this->begin();
			while (pos != this->end())
			{
				if (pos == first)
				{
					std::cout << "here\n";
					while (pos != this->end())
					{
						*pos = *(pos + size);
						pos++;
					}
					this->_size -= size;
					return (last);
				}
				pos++;
			}
			return (last);
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

		void			clear() { this->_size = 0; }
		/* Allocator */
		allocator_type get_allocator() const { return (this->_allocator); };

		vector&		operator=(vector& rhs)
		{
			this->_array = rhs._array;
			this->_size = rhs._size;
			this->_capacity = rhs._capacity;
			this->_allocator = rhs._allocator;
			return (*this);
		}

		friend void		swap(vector<T, Alloc>& x, vector<T, Alloc>& y) { x.swap(y); }
        private:
        
        T*					_array;
        size_type			_size;
        size_type			_capacity;
        allocator_type		_allocator;
    };

	template <class T, class Alloc>
	bool		operator== (const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs)
	{
		if (lhs.size() != rhs.size())
			return (false);
		for (typename vector<T, Alloc>::size_type i = 0; i < lhs.size(); i++)
		{
			if (lhs[i] != rhs[i])
				return (false);
		}
		return (true);
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
		return (!(rhs < lhs));
	}

	template <class T, class Alloc>
	bool operator>= (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
	{
		return (!(lhs < rhs));
	}

}

#endif