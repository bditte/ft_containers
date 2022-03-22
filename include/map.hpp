#ifndef MAP_HPP
# define MAP_HPP

# include "utils/map_utils.hpp"
# include "utils/utils.hpp"
# include "utils/iterator.hpp"

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
		typedef	pair<const Key, mapped_type>					value_type;
		typedef	Compare											key_compare;

		private:

		typedef	ft::tree_node<value_type, key_compare >			node_type;
		typedef ft::AVLTree<value_type, key_compare>				tree;			
		
		public:

		typedef	Allocator										allocator_type;
		typedef	value_type&										reference;
		typedef	const value_type&								const_reference;
		typedef	typename Allocator::pointer						pointer;
		typedef	typename Allocator::const_pointer				const_pointer;
		typedef	std::size_t										size_type;
		typedef	std::ptrdiff_t									difference_type;
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
			_tree(tree()),
			_comp(comp),
			_alloc(alloc),
			_size(0),
			_max_size(MAX_SIZE)
		{}
		
		template <class InputIterator>
					map (typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type first,
					 		InputIterator last,
							const key_compare& comp = key_compare(),
							const allocator_type& alloc = allocator_type()):
			_tree(tree()),
			_comp(comp),
			_alloc(alloc),
			_size(0),
			_max_size(MAX_SIZE)
		{
			this->insert(first, last);
		}

		map(const map& x):
			_tree(tree()),
			_comp(key_compare()),
			_alloc(allocator_type()),
			_size(0),
			_max_size(MAX_SIZE)
		{
			*this = x;
		}

		~map()
		{}

		map& operator=(const map& x)
		{
			if (this == &x)
				return (*this);
			this->clear();
			this->insert(x.begin(), x.end());
			return (*this);
		}
		

		// Iterators

		iterator				begin() { return (iterator(this->_tree.minimum())); }
		const_iterator			begin() const { return (const_iterator(this->_tree.minimum())); }
		iterator				end() { return (iterator(this->_tree.end())); }
		const_iterator			end() const { return (const_iterator(this->_tree.end())); }
		
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
		{	return (this->insert(ft::make_pair(k, mapped_type()))).first->second;}

		// Modifiers

		ft::pair<iterator, bool> insert(const value_type& val)
		{
			pair<iterator, bool> res;

			res.second = !this->count(val.first);
			if (res.second)
			{
				this->_tree.insert(val);
				this->_size++;
			}
			res.first = this->find(val.first);;
			return (res);
		}

		iterator			insert(iterator position, const value_type &val)
		{ (void)position; return (this->insert(val).first); }

		template <class InputIterator>
 		void insert (InputIterator first, InputIterator last)
		{
			while (first != last)
			{
				this->insert(*first++);
			}
		}

		void				erase(iterator position)
		{ this->erase(position->first); }

		size_type			erase(const key_type &k)
		{
			int res = this->_tree.erase(k);
			this->_size -= res;
			return (res);
		}

		void				erase(iterator first, iterator last)
		{
			while (first != last)
			{
				this->erase((first++->first));
			}
		}

		void				swap(map &x)
		{
			size_type	tmp_size = x._size;

			x._size = _size;
			_size = tmp_size;
			_tree.swap(x._tree);
		}

		void				clear()
		{
			
			if (this->_size == 0)
				return ;
			this->_tree.clear();
			this->_size = 0;
		}

		// Oberservers

		key_compare			key_comp() const { return (key_compare()); }
		value_compare		value_comp() const { return (value_compare(key_compare())); }
		
		// Operations

		iterator			find(const key_type &k)
		{
			return (iterator(_tree.find(k)));
		}

		const_iterator			find(const key_type &k) const
		{
			return (const_iterator(_tree.find(k)));
		}

		size_type 			count(const key_type &k) const
		{
			if (!_size)
				return (0);
			if (_tree.count(k))
				return (1);
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

		pair<iterator, iterator>						equal_range(const key_type &k)
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

		private:
	
			tree					_tree;
			key_compare				_comp;
			allocator_type			_alloc;
			size_type				_size;
			size_type				_max_size;
	};

	template <class Key, class T, class Compare, class Alloc>
  	void	swap (map<Key,T,Compare,Alloc>& x, map<Key,T,Compare,Alloc>& y)
	{
		x.swap(y);
	}


	template <class Key, class T, class Compare, class Alloc>
	bool	operator==(const map<Key,T,Compare,Alloc>& lhs,
                    const map<Key,T,Compare,Alloc>& rhs )
	{
		if (lhs.size() != rhs.size())
			return false;
		return (ft::equal(lhs.begin(), lhs.end(), rhs.begin()));
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