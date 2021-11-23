/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bditte <bditte@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 11:06:56 by bditte            #+#    #+#             */
/*   Updated: 2021/11/23 15:13:31 by bditte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector.hpp"
#include <vector>
#if 0
 namespace ft = std;
#endif

int main()
{
    ft::vector<int> myvec(5, 6);
    std::vector<int> stdvec(5, 6);
    std::cout << "myvec size " << myvec.size() << std::endl;
    std::cout << "stdvec size " << stdvec.size() << std::endl;
    return (0);
}