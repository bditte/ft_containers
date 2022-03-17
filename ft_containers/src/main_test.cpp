#include "utils/iterator.hpp"
#include <iterator>
#include <iostream>
#include <vector>
#include <vector.hpp>
#include <map>
#include <map.hpp>
#include <utils/map_iterator.hpp>
#include <utils/map_utils.hpp>
#include <list>
int main()
{
	
	typedef	std::map<int, std::string>				map_t;
	typedef std::map<int, std::string>::iterator	ite_t;
//	typedef	ft::pair<int, std::string>			lst_type;
//	typedef std::list<lst_type>					lst;

	map_t map;
	ite_t	it = map.end();
	it-
	it--;
	std::cout << &(it->first) << std::endl;
	
/*
	typedef ft::rbTree<ft::pair<int, std::string>, std::less<int> > tree_type;
	typedef tree_type::node_ptr	node_ptr;
	tree_type	tree;

	tree.insert(ft::make_pair(1, "test"));
	node_ptr	tmp = tree.search(0);
	std::cout << tmp->right->pos << std::endl;

	tree.clear();
	*/
	return (0);
}