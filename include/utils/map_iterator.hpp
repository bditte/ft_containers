/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_iterator.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bditte <bditte@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/10 11:32:10 by bditte            #+#    #+#             */
/*   Updated: 2022/01/16 19:41:38 by bditte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_ITERATOR_HPP
# define MAP_ITERATOR_HPP

# include <cstddef>

namespace ft
{

template <typename value_type, typename node_type>
class map_iterator
{
	protected:
		node_type	*_node;
		map_iterator(node_type *src): _node(src)
		{}

	public:
		typedef ptrdiff_t			difference_type;
		typedef value_type&			reference;
		typedef	value_type*			pointer;
	
		map_iterator(void): _node(NULL)
		{}
		map_iterator(const map_iterator &src)
		{ *this = src; }
		virtual 		~map_iterator()
		{}
		map_iterator&	operator=(map_iterator const &rhs)
		{ this->_node = rhs._node; return (*this); }

		template <class random_type>
		bool operator==(const map_iterator<random_type, node_type> &rhs) const
		{ return (rhs._node == this->_node); }

		template <class random_type>
		bool operator!=(const map_iterator<random_type, node_type> &rhs) const
		{ return (rhs._node != this->_node); }

		map_iterator	&operator++(void)
		{
			if (this->_node->right != NULL)
				this->_node = node_min(this->_node->right);
			else
			{
				node_type	*tmp = this->_node;
				
				this->_node = this->_node->parent;
				while (this->_node && tmp == this->_node->right)
				{
					tmp = this->_node;
					this->_node = this->_node->parent;
				}
			}
			return (*this);
		}
		map_iterator	operator++(int)
		{
			map_iterator res(*this);
			++(*this);
			return (res);
		}
		map_iterator	&operator--(void)
		{
			if (this->_node->left != NULL)
					this->_node = node_max(this->_node->left);
			else
			{
				node_type	*tmp = this->_node;
				
				this->_node = this->_node->parent;
				while (this->_node && tmp == this->_node->left)
				{
					tmp = this->_node;
					this->_node = this->_node->parent;
				}
			}
			return (*this);
		}
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

		operator		map_iterator<const value_type, node_type>() const
		{ return map_iterator<const value_type, node_type>(this->_node); }

		template <class, class, class, class>
		friend class map;

		template <class, class>
		friend class map_iterator;
};
}
#endif