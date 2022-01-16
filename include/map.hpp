#ifndef MAP_HPP
# define MAP_HPP

# include "utils/BSTree.hpp"
# include <functional>
# include <iostream>
# include <limits>
# include <utils/map_iterator.hpp>
# include <utils/map_utils.hpp>
# include <utils/utils.hpp>
# include <utils/vector_iterator.hpp>

# define MAX_SIZE  allocator_type().max_size() / (sizeof(node_type))

namespace ft
{
	template<
		class Key,
		class T,
		class Compare = std::less<Key>,
		class Allocator = std::allocator<std::pair<const Key, T> >
	> class map
	{
		public:

		typedef	Key												key_type;
		typedef	T												mapped_type;
		typedef	pair<const Key, T>								value_type;
		typedef	Compare											key_compare;			
		

		typedef	Allocator										allocator_type;
		typedef	value_type&										reference;
		typedef	const value_type&								const_reference;
		typedef	typename Allocator::pointer						pointer;
		typedef	typename Allocator::const_pointer				const_pointer;
		typedef	std::size_t										size_type;
		typedef	std::ptrdiff_t									difference_type;
	
		typedef ft::tree_node<value_type>						node_type;
		typedef node_type*										node_ptr;


		typedef map_iterator<value_type, node_type>				iterator;
		typedef map_iterator<const value_type, node_type>		const_iterator;
		typedef ft::reverse_iterator<iterator>					reverse_iterator;
		typedef ft::reverse_iterator<const_iterator>			const_reverse_iterator;
		
		class value_compare
		{  
			
			public:

			Compare comp;
			value_compare (Compare c) : comp(c) {}

			typedef bool result_type;
			typedef value_type first_argument_type;
			typedef value_type second_argument_type;
			bool operator() (const value_type& x, const value_type& y) const
			{
				return comp(x.first, y.first);
			}

		};

		explicit	map(const key_compare& comp = key_compare(),
						const allocator_type& alloc = allocator_type() ):
			_tree(),
			_comp(comp),
			_alloc(alloc),
			_size(0),
			_max_size(MAX_SIZE)
		{
			this->_tree = new node_type;
		}
		
		template <class InputIterator>
					map (typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type first,
					 		InputIterator last,
							const key_compare& comp = key_compare(),
							const allocator_type& alloc = allocator_type()):
			_tree(),
			_comp(comp),
			_alloc(alloc),
			_size(0),
			_max_size(MAX_SIZE)
		{ 
			this->_tree = new node_type;
			this->insert(first, last);
		}

		map(const map& x):
			_tree(),
			_comp(key_compare()),
			_alloc(allocator_type()),
			_size(0),
			_max_size(MAX_SIZE)
		{
			this->_tree = new node_type;
			*this = x;
		}

		~map()
		{
			this->clear();
			delete this->_tree;
		}

		map& operator=(const map& x)
		{
			if (this == &x)
				return (*this);
			this->clear();
			this->insert(x.begin(), x.end());
			return (*this);
		}
		

		// Iterators

		iterator				begin() { return (iterator(node_min(this->_tree))); }
		const_iterator			begin() const { return (const_iterator(node_min(this->_tree))); }
		iterator				end() { return (iterator(node_max(this->_tree))); }
		const_iterator			end() const { return (const_iterator(node_max(this->_tree))); }
		
		reverse_iterator		rbegin() { return reverse_iterator(this->end()); }
		const_reverse_iterator 	rbegin() const { return const_reverse_iterator(this->end()); }
		reverse_iterator		rend() { return reverse_iterator(this->begin()); }
		const_reverse_iterator	rend() const { return const_reverse_iterator(this->begin()); }
		// Capacity

		bool				empty() const
		{
			if (!this->_size)
				return (true);
			return (false);
		}
		size_type			size() const { return (this->_size); };
		size_type			max_size() const { return (this->_max_size); };

		// Element Access

		mapped_type			&operator[](const key_type &k)
		{	return (this->insert(value_type(k, mapped_type()))).first->second;}

		// Modifiers

		pair<iterator, bool> insert(const value_type& val)
		{
			pair<iterator, bool> res;

			res.second = !this->count(val.first);
			if (res.second)
				this->tree_add(new node_type(val));
			res.first = this->find(val.first);
			return (res);
		}

		iterator			insert(iterator position, const value_type &val)
		{ (void)position; return (this->insert(val).first); }

		template <class InputIterator>
 		void insert (InputIterator first, InputIterator last)
		{
			while (first != last)
			{
				this->insert(*first);
				first++;
			}
		}

		void				erase(iterator position)
		{ this->erase(position++, position); }

		size_type			erase(const key_type &k)
		{
			iterator tmp = this->find(k);

			if (tmp == this->end())
				return (0);
			this->tree_remove(tmp._node);
			return (1);
		}

		void				erase(iterator first, iterator last)
		{
			while (first != last)
			{
				this->tree_remove(first._node);
				first++;
			}
		}

		void				swap(map &x)
		{
			map	tmp;

			tmp.cpy_map(x);
			x.cpy_map(*this);
			this->cpy_map(tmp);
		}

		void				clear()
		{
			node_ptr	tmp = this->end()._node;
	
			if (this->_size == 0)
				return ;
			tmp->parent->right = NULL;
			this->tree_clear(this->_tree);
			this->_tree = tmp;
			this->_size = 0;		
		}

		// Oberservers

		key_compare			key_comp() const { return (key_compare()); }
		value_compare		value_comp() const { return (value_compare(key_compare())); }
		
		// Operations

		iterator			find(const key_type &k)
		{
			iterator first = this->begin();
			iterator last = this->end();

			while (first != last)
			{
				if (this->check_keys(first->first, k))
					return (first);
				first++;
			}
			return (first);
		}

		const_iterator			find(const key_type &k) const
		{
			const_iterator first = this->begin();
			const_iterator last = this->end();

			while (first != last)
			{
				if (this->check_keys(first->first, k))
					return (first);
				first++;
			}
			return (first);
		}

		size_type 			count(const key_type &k) const
		{
			const_iterator	first = this->begin();
			const_iterator	last = this->end();

			while (first != last)
			{
				if (this->check_keys(first->first, k))
					return (1);
				first++;
			}
			return (0);
		}

		iterator			lower_bound(const key_type &k)
		{
			iterator tmp = this->begin();
			iterator last = this->end();

			while (tmp != last)
			{
				if (!this->_comp(tmp->first, k))
					break;
				++tmp;
			}
			return tmp;
		}

		const_iterator		lower_bound(const key_type &k) const
		{
			const_iterator tmp = this->begin();
			const_iterator last = this->end();

			while (tmp != last)
			{
				if (!this->_comp(tmp->first, k))
					break;
				++tmp;
			}
			return tmp;
		}

		iterator			upper_bound(const key_type &k)
		{
			iterator tmp = this->begin();
			iterator last = this->end();

			while (tmp != last)
			{
				if (this->_comp(k, tmp->first))
					break;
				++tmp;
			}
			return tmp;
		}

		const_iterator		upper_bound(const key_type &k) const
		{
			const_iterator tmp = this->begin();
			const_iterator last = this->end();

			while (tmp != last)
			{
				if (this->_comp(k, tmp->first))
					break;
				++tmp;
			}
			return tmp;
		}

		pair<iterator, iterator>			equal_range(const key_type &k)
		{
			pair<iterator, iterator> res;

			res.first = this->lower_bound(k);
			res.second = this->upper_bound(k);

			return (res);
		}

		pair<const_iterator, const_iterator>			equal_range(const key_type &k) const
		{
			pair<const_iterator, const_iterator> res;

			res.first = this->lower_bound(k);
			res.second = this->upper_bound(k);

			return (res);
		}
		// DEBUG FUNCTIONS

		private:
			node_ptr				_tree;
			key_compare				_comp;
			allocator_type			_alloc;
			size_type				_size;
			size_type				_max_size;

			void					tree_add(node_ptr src)
			{
				node_ptr 	*parent = &this->_tree;
				node_ptr 	*node = &this->_tree;
				node_ptr 	tmp = node_max(this->_tree);
				bool		is_left = -1;
				
				this->_size++;
				while (*node && *node != tmp)
				{
					parent = node;
					is_left = this->_comp(src->data.first, (*node)->data.first);
					if (is_left)
						node = &(*node)->left;
					else
						node = &(*node)->right;
				}
				if (*node == NULL)
				{
					src->parent = (*parent);
					*node = src;
				}
				else
				{
					*node = src;
					src->parent = tmp->parent;
					tmp->parent = node_max(src);
					node_max(src)->right = tmp;
				}
			}

			void					tree_remove(node_ptr src)
			{
				node_ptr	tmp = NULL;
				node_ptr	*sub = &this->_tree;

				this->_size--;
				if (src->parent)
				{
					if (src->parent->left == src)
						sub = &src->parent->left;
					else
						sub = &src->parent->right;
				}
				if (src->left == NULL && src->right == NULL)
					;
				else if (src->left == NULL)
					tmp = src->right;
				else
				{
					tmp = node_max(src->left);
					if (tmp != src->left)
						if ((tmp->parent->right = tmp->left))
							tmp->left->parent = tmp->parent;
				}
				if (tmp)
				{
					tmp->parent = src->parent;
					if (src->left && src->left != tmp)
					{
						tmp->left = src->left;
						tmp->left->parent = tmp;
					}
					if (src->right && src->right != tmp)
					{
						tmp->right = src->right;
						tmp->right->parent = tmp;
					}
				}
				*sub = tmp;
				delete src;
			}

			void					tree_clear(node_ptr root)
			{
				if (root == NULL)
				 	return ;
				this->tree_clear(root->left);
				this->tree_clear(root->right);
				delete root;
			}

			void					cpy_map(map &src)
			{
				this->clear();
				node_ptr tmp = this->_tree;

				this->_tree = src._tree;
				this->_comp = src._comp;
				this->_alloc = src._alloc;
				this->_size = src._size;
				src._tree = tmp;
				src._size = 0;
				tmp = NULL;
			}
	
			bool					check_keys(const key_type &a, const key_type &b) const
			{ return (!this->_comp(a, b) && !this->_comp(b, a)); }
	};

	template <class Key, class T, class Compare, class Alloc>
	bool	operator==(const map<Key,T,Compare,Alloc>& lhs,
                    const map<Key,T,Compare,Alloc>& rhs )
	{
		if (lhs.size() != rhs.size())
			return false;
		return (is_same_map(lhs.begin(), lhs.end(), rhs.begin()));
	}

	template <class Key, class T, class Compare, class Alloc>
  	bool operator!= ( const map<Key,T,Compare,Alloc>& lhs,
                    const map<Key,T,Compare,Alloc>& rhs )
	{ return !(lhs == rhs); }

	template <class Key, class T, class Compare, class Alloc>
  	bool operator<  ( const map<Key,T,Compare,Alloc>& lhs,
                    const map<Key,T,Compare,Alloc>& rhs )
	{ return (is_inferior(lhs.begin(), lhs.end(), rhs.begin(), rhs.end())); }

	template <class Key, class T, class Compare, class Alloc>
	bool operator<= ( const map<Key,T,Compare,Alloc>& lhs,
						const map<Key,T,Compare,Alloc>& rhs )
	{ return !(rhs < lhs); }

	template <class Key, class T, class Compare, class Alloc>
	bool operator>  ( const map<Key,T,Compare,Alloc>& lhs,
						const map<Key,T,Compare,Alloc>& rhs )
	{ return (rhs < lhs); }

	template <class Key, class T, class Compare, class Alloc>
 	bool operator>= ( const map<Key,T,Compare,Alloc>& lhs,
                    const map<Key,T,Compare,Alloc>& rhs)
	{ return (!(lhs < rhs)); }
};

#endif