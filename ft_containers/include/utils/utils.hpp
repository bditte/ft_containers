#ifndef UTILS_HPP
# define UTILS_HPP

# include <string>
# include <sstream>
# include <cstddef>
# include <iostream>
# include <cstdlib>
# include <functional>
# include <limits>

namespace ft 
{
	template < bool Cond, class T = void>
	struct enable_if {};

	template<class T> struct enable_if<true, T> { typedef T type; };

	template <class T, T v>
	struct integral_constant
	{
		const static T value = v;
		typedef T							value_type;
		typedef	integral_constant<T, v>		type;
	};

	typedef	integral_constant<bool, true>		true_type;
	typedef	integral_constant<bool, false>		false_type;
	

	template <class T>
	struct is_integral: false_type {};

	template <class T>
	struct is_integral<const T>: is_integral<T> {};

	template <class T>
	struct is_integral<volatile T>: is_integral<T> {};

	template <>
	struct is_integral<bool>: true_type {};

	template <>
	struct is_integral<char>: true_type {};

	template <>
	struct is_integral<wchar_t>: true_type {};

	template <>
	struct is_integral<signed char>: true_type {};

	template <>
	struct is_integral<short int>: true_type {};

	template <>
	struct is_integral<int>: true_type {};
	
	template <>
	struct is_integral<long int>: true_type {};

	template <>
	struct is_integral<long long int>: true_type {};

	template <>
	struct is_integral<unsigned char>: true_type {};

	template <>
	struct is_integral<unsigned short int>: true_type {};

	template <>
	struct is_integral<unsigned int>: true_type {};

	template <>
	struct is_integral<unsigned long int>: true_type {};

	template <>
	struct is_integral<unsigned long long int>: true_type {};


	// Functions
	

	template <class InputIterator1, class InputIterator2>
  	bool equal (InputIterator1 first1, InputIterator1 last1, InputIterator2 first2)
	{
		while (first1 != last1)
		{
			if (!(*first1 == *first2))
				return (false);
			++first1; ++first2;
		}
		return (true);
	}

	template <class InputIterator1, class InputIterator2, class BinaryPredicate>
  	bool equal (InputIterator1 first1, InputIterator1 last1, InputIterator2 first2, BinaryPredicate pred)
	{
		while (first1 != last1)
		{
			if (!pred(first1, first2))
				return (false);
			++first1; ++first2;
		}
		return (true);
	}

	template <class InputIterator1, class InputIterator2>
  	bool lexicographical_compare (InputIterator1 first1, InputIterator1 last1, InputIterator2 first2, InputIterator2 last2)
	{
		while (first1 != last1)
		{
			if (first2 == last2 || *first2 < *first1)
				return false;
			else if (*first1 < *first2)
				return true;
			++first1; ++first2;
		}
		return (first2 != last2);
	}

	template <class InputIterator1, class InputIterator2, class Compare>
  	bool lexicographical_compare (InputIterator1 first1, InputIterator1 last1, InputIterator2 first2, InputIterator2 last2, Compare comp)
	{
		while (first1 != last1)
		{
			if (first2 == last2 || *first2 < *first1)
				return false;
			else if (comp(*first1, *first2))
				return true;
			++first1; ++first2;
		}
		return (first2 != last2);
	}

	template <class T>
	const T& min(const T& a, const T& b)
	{ return ((a <= b) ? a : b); }

	template <class T>
	const T& max(const T& a, const T& b)
	{ return ((a >= b) ? a : b); }
}

#endif