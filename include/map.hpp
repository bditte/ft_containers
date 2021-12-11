#ifndef MAP_HPP
# define MAP_HPP

# include "utils/BSTree.hpp"
# include <functional>
# include <iostream>
# include <utils/iterator.hpp>

namespace ft
{
	template<
		class Key,
		class T,
		class Compare = std::less<Key>,
		class Allocator = std::allocator<std::pair<const Key, T> >
	> class map
	{
		typedef	Key										key_type;
		typedef	T										mapped_type;
		typedef	std::pair<const Key, T>					value_type;
		typedef	std::size_t								size_type;
		typedef	std::ptrdiff_t							difference_type;
		typedef	Compare									key_compare;
		typedef	Allocator								allocator_type;
		typedef	value_type&								reference;
		typedef	const value_type&						const_reference;
		typedef	typename Allocator::pointer				pointer;
		typedef	typename Allocator::const_pointer		const_pointer;
		typedef	BSTree<Key, T>							tree;
		typedef	myIterator<value_type>					iterator;


		public:
			explicit		map(const key_compare& comp = key_compare(),
							const allocator_type& alloc = allocator_type() ):
				_tree(comp, alloc),
				_comp(comp),
				_alloc(alloc)
			{}

		// Modifiers

		// need to add correct ret value
		void				insert(const value_type& val)
		{
			_tree.insert(_tree.getRoot(), val);
		}

		// DEBUG FUNCTIONS
		void				display(){	_tree.display(); }

		private:
			tree				_tree;
			key_compare			_comp;
			allocator_type		_alloc;
	};			
};

#endif