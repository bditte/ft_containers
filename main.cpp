/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bditte <bditte@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 11:06:56 by bditte            #+#    #+#             */
/*   Updated: 2021/11/24 12:55:24 by bditte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector.hpp"
#include <vector>
#include <stdexcept>

#if 0
 namespace ft = std;
#endif

#define VALUE 23
int main()
{
    ft::vector<int> myvec(10, 6);
	ft::vector<int> cpyvec(myvec);
    std::vector<int> stdvec(10, 6);

    std::cout << "myvec size " << myvec.size() << std::endl;
	std::cout << "cpyvec size " << cpyvec.size() << std::endl;
	std::cout << "stdvec size " << stdvec.size() << std::endl;
    std::cout << "stdvec capacity " << stdvec.capacity() << std::endl;
	/*
	std::cout << myvec.empty() << std::endl;
	std::cout << cpyvec.empty() << std::endl;
	std::cout << stdvec.empty() << std::endl;
	*/
 	//std::cout << "max " << stdvec.max_size() << std::endl;
	std::cout << "myvec size " << myvec.size() << std::endl;
	std::cout << "myvec capacity " << myvec.capacity() << std::endl;
	std::cout << "stdvec size " << stdvec.size() << std::endl;
	std::cout << "stdvec capacity " << stdvec.capacity() << std::endl;
    return (0);
}