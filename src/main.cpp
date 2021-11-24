/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bditte <bditte@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 11:06:56 by bditte            #+#    #+#             */
/*   Updated: 2021/11/24 14:40:30 by bditte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector.hpp"
#include <vector>
#include <stdexcept>

#if 0
 namespace ft = std;
#endif

#define VALUE 0
int main()
{
    ft::vector<int> myvec(10, 3);
	ft::vector<int> cpyvec(myvec);
	ft::vector<int> const constvec(10, 3);
    std::vector<int> stdvec(10, 3);

    std::cout << "myvec size " << myvec.size() << std::endl;
	std::cout << "cpyvec size " << cpyvec.size() << std::endl;
	std::cout << "stdvec size " << stdvec.size() << std::endl;
    std::cout << "stdvec capacity " << stdvec.capacity() << std::endl;
	
	/*
	std::cout << myvec.empty() << std::endl;
	std::cout << cpyvec.empty() << std::endl;
	std::cout << stdvec.empty() << std::endl;
	*/

 	std::cout << "max " << stdvec.max_size() << std::endl;
	try
	{
		stdvec.assign(5, 30);
		std::cout << stdvec[2] <<std::endl;
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << '\n';
	}
	try
	{
		myvec.assign(5, 30);
		std::cout << myvec[2] <<std::endl;
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << '\n';
	}
	try
	{
		std::cout << constvec.data() << std::endl;
		//constvec.assign(15, 30);
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << '\n';
	}
	
	std::cout << "myvec size " << myvec.size() << std::endl;
	std::cout << "myvec capacity " << myvec.capacity() << std::endl;
	std::cout << "stdvec size " << stdvec.size() << std::endl;
	std::cout << "stdvec capacity " << stdvec.capacity() << std::endl;
    return (0);
}