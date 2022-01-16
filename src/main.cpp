#include "map.hpp"
#include "vector.hpp"
#include "stack.hpp"

#include <vector>
#include <map>
#include <stack>

#include <iostream>
#include <string>

#ifndef NAMESPACE
# define NAMESPACE ft
#endif

using namespace NAMESPACE;

int	main()
{
	vector<int> vec(8, 8);

	for (vector<int>::iterator it = vec.begin(); it != vec.end(); it++)
		std::cout << *it << std::endl;
	return (0);
}
