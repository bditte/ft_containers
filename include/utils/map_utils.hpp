#ifndef MAP_UTILS_HPP
# define MAP_UTILS_HPP

namespace ft
{

//Pair struct

template <class U, class T>
struct pair
{
	typedef U	first_type;
	typedef T	second_type;

	first_type	first;
	second_type	second;

	pair():
		first(),
		second()
	{};
	template<class V, class W>
	pair(const pair<V, W> &src):
		first(src.first),
		second(src.second)
	{};
	pair(const first_type &arg1, const second_type &arg2):
		first(arg1),
		second(arg2)
	{};

	pair	&operator=(const pair &src)
	{
		if (this == &src)
			return (*this);
		this->first = src.first;
		this->second = src.second;
		return (*this);
	}
};

// Pair operators
template <class U, class T>
bool operator==(const pair<U, T> &lhs, const pair<U, T> &rhs) {
	return (lhs.first == rhs.first && lhs.second == rhs.second);
}

template <class U, class T>
bool operator!=(const pair<U, T> &lhs, const pair<U, T> &rhs) {
	return !(lhs == rhs);
}

template <class U, class T>
bool operator< (const pair<U, T> &lhs, const pair<U, T> &rhs) {
	return lhs.first < rhs.first || (!(rhs.first < lhs.first) && lhs.second < rhs.second);
}

template <class U, class T>
bool operator<=(const pair<U, T> &lhs, const pair<U, T> &rhs) {
	return !(rhs < lhs);
}

template <class U, class T>
bool operator> (const pair<U, T> &lhs, const pair<U, T> &rhs) {
	return (rhs < lhs);
}

template <class U, class T>
bool operator>=(const pair<U, T> &lhs, const pair<U, T> &rhs) {
	return !(lhs < rhs);
}

//Map tree declaration

template <typename value_type>
struct tree_node
{
	public:
	value_type		data;
	tree_node		*parent;
	tree_node		*left;
	tree_node		*right;

	tree_node(const value_type&src = value_type()): 
		data(src), 
		parent(NULL), 
		left(NULL), 
		right(NULL)
	{};
};

template <typename T>
tree_node<T> *node_max(tree_node<T> *root)
{
	while (root->right)
		root = root->right;
	return (root);
}

template <typename T>
tree_node<T> *node_min(tree_node<T> *root)
{
	while (root->left)
		root = root->left;
	return (root);
}


// Map utils functions

template <class Iterator>
bool	is_same_map(Iterator first, Iterator last, Iterator first2)
{
	while (first != last)
	{
		if (*first != *first2)
			return false;
		first++;
		first2++;
	}
	return (true);
}

template <class Iterator>
bool	is_inferior(Iterator first1, Iterator last1, Iterator first2, Iterator last2)
{
	while (first1 != last1 && first2 != last2 && *first1 == *first2)
	{
		first1++;
		first2++;
	}
	if (first1 == last1)
		return (first2 != last2);
	else if (first2 == last2)
		return (false);
	return (*first1 < *first2);
}

}
#endif