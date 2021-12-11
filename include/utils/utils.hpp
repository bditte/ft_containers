#ifndef UTILS_HPP
# define UTILS_HPP

#include <string>
#include <sstream>

namespace ft 
{
	std::string	int_to_str(const int n)
	{
		std::stringstream ss;
		ss << n;
		return (ss.str());
	}

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

}

#endif