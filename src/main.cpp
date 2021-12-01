/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bditte <bditte@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 11:06:56 by bditte            #+#    #+#             */
/*   Updated: 2021/12/01 13:08:35 by bditte           ###   ########.fr       */
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
	ft::vector<int> 			cpyvec(3, 10);
	ft::vector<int> const 		constvec(10, 3);
    std::vector<int> 			stdvec(10, 3);
	std::vector<int> 			stdcpy(3, 10);
	ft::vector<int>::iterator	myit ;
	ft::vector<int>::const_iterator	constit = myvec.begin() ;
	std::vector<int>::iterator 	stdit ;

	size_t	old_ft_size = myvec.size();
	size_t	old_ft_capacity = myvec.capacity();
	size_t	old_std_size = myvec.size();
	size_t	old_std_capacity = myvec.capacity();

	myvec.clear();
	stdvec.clear();


	//stdvec.insert(stdvec.begin(), 8);
	//myvec.insert(myvec.begin(), 8);
	//stdvec.insert(stdvec.begin(), 4, 7);
	//stdvec.insert(stdvec.end() - 2, 4, -7);
	//myvec.insert(myvec.begin(), 4, 7);

    std::cout << "myvec old_size " << old_ft_size  << " new size : " << myvec.size()<< std::endl;
	std::cout << "myvec old_capacity " << old_ft_capacity  << " new capacity : " << myvec.capacity() << std::endl;
	std::cout << "stdvec old_size " << old_std_size  << " new size : " << stdvec.size()<< std::endl;
	std::cout << "stdvec old_capacity " << old_std_capacity  << " new capacity : " << stdvec.capacity()<< std::endl;
	std::cout << myvec.empty() << std::endl;
	std::cout << stdvec.empty() << std::endl;
	std::cout << myvec.back() << std::endl;
	std::cout << stdvec.back() << std::endl;

	std::cout << "myvec: ";
	for (ft::vector<int>::iterator it = myvec.begin(); it != myvec.end(); it++)
		std::cout << *it << " ";
	std::cout << std::endl << "stdvec: ";
	for (std::vector<int>::iterator it = stdvec.begin(); it != stdvec.end(); it++)
		std::cout << *it << " ";
	/*for (int i = 0; cpybegin != stdcpy.end(); cpybegin++)
	{
		std::cout << *cpybegin << " ";
		i++;
	}*/
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
    return (0);*/
}