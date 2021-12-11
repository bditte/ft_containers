/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_map.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bditte <bditte@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 11:06:56 by bditte            #+#    #+#             */
/*   Updated: 2021/12/11 10:48:36 by bditte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils/BSTree.hpp"
#include "map.hpp"
#include <vector>
#include <stdexcept>
#include <map>

#if 0
 namespace ft = std;
#endif

#include <cstdlib>

#define VALUE 0
int main()
{
	ft::map<int, std::string> ftmap;
	std::map<int, std::string> stdmap;

	stdmap.insert(std::pair<int, std::string>(5, "cinq"));
	stdmap.insert(std::pair<int, std::string>(1, "un"));
	stdmap.insert(std::pair<int, std::string>(50, "cinquante"));
	stdmap.insert(std::pair<int, std::string>(20, "vingt"));
	
	for (std::map<int, std::string>::iterator i = stdmap.begin(); i != stdmap.end(); i++)
		std::cout << i->second << std::endl;

	ftmap.insert(std::pair<int, std::string>(5, "cinq"));
	ftmap.insert(std::pair<int, std::string>(1, "un"));
	ftmap.insert(std::pair<int, std::string>(50, "cinquante"));
	ftmap.insert(std::pair<int, std::string>(20, "vingt"));
	ftmap.display();
}