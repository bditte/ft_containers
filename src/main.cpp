/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bditte <bditte@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 11:06:56 by bditte            #+#    #+#             */
/*   Updated: 2021/11/30 15:32:05 by bditte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector.hpp"
#include <vector>
#include <stdexcept>

#if 0
 namespace ft = std;
#endif

#include <cstdlib>

#define VALUE 0
int main()
{
    ft::vector<int> 			myvec(10, 3);
	ft::vector<int> 			emptyvec;
	ft::vector<int> 			cpyvec(myvec);
	ft::vector<int> const 		constvec(10, 3);
    std::vector<int> 			stdvec(10, 3);
	ft::vector<int>::iterator	myit ;
	std::vector<int>::iterator 	stdit ;

	stdvec.resize(5);
    std::cout << "myvec size " << myvec.size() << std::endl;
	std::cout << "cpyvec size " << cpyvec.size() << std::endl;
	std::cout << "stdvec size " << stdvec.size() << std::endl;
	std::cout << "emptyvec size " << emptyvec.size() << std::endl;
	std::cout << "myvec capacity " << myvec.capacity() << std::endl;
    std::cout << "stdvec capacity " << stdvec.capacity() << std::endl;
	exit(0);
	myit = myvec.begin() + 2;
	myvec[0] = 99;
	//myit = myvec.insert(myvec.begin() + 200, 66);
	stdvec.resize(15);
	/*stdvec[0] = 99;

	std::cout << "Here\n";
	stdit = stdvec.begin() + 2;
	stdit = stdvec.insert(stdvec.begin() + 2, 66);*/

	std::cout << "Here\n";
/*	std::cout << "my iterator value : " << myvec[0] << std::endl;
	std::cout << "my iterator value : " << myvec[1] << std::endl;
	std::cout << "my iterator value : " << *myit << std::endl;
	std::cout << "std iterator value : " << stdvec[0] << std::endl;
	std::cout << "std iterator value : " << stdvec[1] << std::endl;
	std::cout << "std iterator value : " << (stdvec[12]) << std::endl;

	for (size_t i = 0; i < myvec.size(); i++)
		std::cout << "vec :" << myvec[i] << std::endl;
*/
	std::cout << "Here\n";
	std::cout << "myvec size " << myvec.size() << std::endl;
	std::cout << "myvec capacity " << myvec.capacity() << std::endl;
    std::cout << "stdvec capacity " << stdvec.capacity() << std::endl;
	std::cout << "stdvec size " << stdvec.size() << std::endl;
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