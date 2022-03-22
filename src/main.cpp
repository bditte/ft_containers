

#include <iomanip>
#include <iostream>
#include <string>
#include <deque>
#include <time.h>
#include <stdlib.h>

#define MAX_RAM 4294967296
#define BUFFER_SIZE 4096
struct Buffer
{
	int idx;
	char buff[BUFFER_SIZE];
};

#include <vector>
#include <map>
#include <stack>

#include "map.hpp"
#include "vector.hpp"
#include "stack.hpp"

#define COUNT		300000

#ifndef STD
#  define STD 0
#endif

#include <iostream>
#include <string>


template<typename T>
class ft_MutantStack : public ft::stack<T>
{
public:
	ft_MutantStack() {}
	ft_MutantStack(const ft_MutantStack<T>& src) { *this = src; }
	ft_MutantStack<T>& operator=(const ft_MutantStack<T>& rhs) 
	{
		this->c = rhs.c;
		return *this;
	}
	~ft_MutantStack() {}

	typedef typename ft::stack<T>::container_type::iterator iterator;

	iterator begin() { return this->c.begin(); }
	iterator end() { return this->c.end(); }
};

double ft_tests(const int seed)
{

	clock_t			start_time = clock();
	srand(seed);

	ft::vector<std::string> vector_str;
	ft::vector<int> vector_int;
	ft::stack<int> stack_int;
	ft::vector<Buffer> vector_buffer;
	ft::stack<Buffer, std::deque<Buffer> > stack_deq_buffer;
	ft::map<int, int> map_int;

	for (int i = 0; i < COUNT; i++)
	{
		vector_buffer.push_back(Buffer());
	}
	for (int i = 0; i < COUNT; i++)
	{
		const int idx = rand() % COUNT;
		vector_buffer[idx].idx = 5;
	}

	ft::vector<Buffer>().swap(vector_buffer);

	try
	{
		for (int i = 0; i < COUNT; i++)
		{
			const int idx = rand() % COUNT;
			vector_buffer.at(idx);
			std::cerr << "Error: THIS VECTOR SHOULD BE EMPTY!!" <<std::endl;
		}
	}
	catch(const std::exception& e)
	{
		//NORMAL ! :P
	}
	for (int i = 0; i < COUNT; ++i)
	{
		map_int.insert(ft::make_pair(rand(), rand()));
	}

	int sum = 0;
	for (int i = 0; i < 10000; i++)
	{
		int access = rand();
		sum += map_int[access];
	}
	std::cout << "should be constant with the same seed: " << sum << std::endl;

	{
		ft::map<int, int> copy = map_int;
	}
	ft_MutantStack<char> iterable_stack;
	for (char letter = 'a'; letter <= 'z'; letter++)
		iterable_stack.push(letter);
	for (ft_MutantStack<char>::iterator it = iterable_stack.begin(); it != iterable_stack.end(); it++)
	{
		std::cout << *it;
	}
	std::cout << std::endl;

	clock_t	end_time = clock();
	double total_time = double(end_time - start_time) / double(CLOCKS_PER_SEC);
	std::cout << std::endl << "\033[1;37mFT Total execution time : " << std::fixed << total_time  << "sec" << std::endl;
	return (total_time);
}


template<typename T>
class std_MutantStack : public std::stack<T>
{
public:
	std_MutantStack() {}
	std_MutantStack(const std_MutantStack<T>& src) { *this = src; }
	std_MutantStack<T>& operator=(const std_MutantStack<T>& rhs) 
	{
		this->c = rhs.c;
		return *this;
	}
	~std_MutantStack() {}

	typedef typename std::stack<T>::container_type::iterator iterator;

	iterator begin() { return this->c.begin(); }
	iterator end() { return this->c.end(); }
};

double std_tests(const int seed) {

	clock_t			start_time = clock();

	srand(seed);

	std::vector<std::string> vector_str;
	std::vector<int> vector_int;
	std::stack<int> stack_int;
	std::vector<Buffer> vector_buffer;
	std::stack<Buffer, std::deque<Buffer> > stack_deq_buffer;
	std::map<int, int> map_int;

	for (int i = 0; i < COUNT; i++)
	{
		vector_buffer.push_back(Buffer());
	}
	for (int i = 0; i < COUNT; i++)
	{
		const int idx = rand() % COUNT;
		vector_buffer[idx].idx = 5;
	}

	std::vector<Buffer>().swap(vector_buffer);

	try
	{
		for (int i = 0; i < COUNT; i++)
		{
			const int idx = rand() % COUNT;
			vector_buffer.at(idx);
			std::cerr << "Error: THIS VECTOR SHOULD BE EMPTY!!" <<std::endl;
		}
	}
	catch(const std::exception& e)
	{
		//NORMAL ! :P
	}
	for (int i = 0; i < COUNT; ++i)
	{
		map_int.insert(std::make_pair(rand(), rand()));
	}
	int sum = 0;
	for (int i = 0; i < 10000; i++)
	{
		int access = rand();
		sum += map_int[access];
	}
	std::cout << "should be constant with the same seed: " << sum << std::endl;

	{
		std::map<int, int> copy = map_int;
	}
	std_MutantStack<char> iterable_stack;
	for (char letter = 'a'; letter <= 'z'; letter++)
		iterable_stack.push(letter);
	for (std_MutantStack<char>::iterator it = iterable_stack.begin(); it != iterable_stack.end(); it++)
	{
		std::cout << *it;
	}
	std::cout << std::endl;

	clock_t	end_time = clock();
	double total_time = double(end_time - start_time) / double(CLOCKS_PER_SEC);
	std::cout << std::endl << "\033[1;37mSTD Total execution time : " << std::fixed << total_time  << "sec\033[0;0m" << std::endl;
	return (total_time);
}

int main(int argc, char **argv)
{
	if (argc != 2)
	{
		std::cerr << "Usage: ./test seed" << std::endl;
		std::cerr << "Provide a seed please" << std::endl;
		std::cerr << "Count value:" << COUNT << std::endl;
		return 1;
	}
	const int seed = atoi(argv[1]);
	
	double std_time = 0;
	double ft_time = 0;

	if (STD == 1)
		std_time = std_tests(seed);
	else 
		std_time = ft_tests(seed);
	(void)std_time;
	(void)ft_time;
	/*double ratio = ft_time / std_time;
	
	if (ratio > 20)
		std::cout << "\033[1;31m[KO] : ft containers are " << ratio << "times slower." << std::endl;
	else if (ratio > 0)
		std::cout << "\033[1;32m[OK] : ft containers are " << ratio << "times slower." << std::endl;
	else
		std::cout << "\033[1;32m[GG] : ft containers are " << std_time / ft_time << "times faster." << std::endl;*/
	return (0);
}