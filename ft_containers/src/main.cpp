

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

#if 0
	#include <vector>
	#include <map>
	#include <stack>
	namespace ft = std;
#else
	#include "map.hpp"
	#include "vector.hpp"
	#include "stack.hpp"
#endif

#define COUNT 100//(MAX_RAM / (int)sizeof(Buffer))

#ifndef NAMESPACE
# define NAMESPACE ft
#endif

template<typename T>
class MutantStack : public ft::stack<T>
{
public:
	MutantStack() {}
	MutantStack(const MutantStack<T>& src) { *this = src; }
	MutantStack<T>& operator=(const MutantStack<T>& rhs) 
	{
		this->c = rhs.c;
		return *this;
	}
	~MutantStack() {}

	typedef typename ft::stack<T>::container_type::iterator iterator;

	iterator begin() { return this->c.begin(); }
	iterator end() { return this->c.end(); }
};


using namespace NAMESPACE;

int main(int argc, char** argv) {

	clock_t			start_time = clock();
	if (argc != 2)
	{
		std::cerr << "Usage: ./test seed" << std::endl;
		std::cerr << "Provide a seed please" << std::endl;
		std::cerr << "Count value:" << COUNT << std::endl;
		return 1;
	}
	const int seed = atoi(argv[1]);
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
	std::cout << COUNT << " " << vector_buffer.size() << " "<< vector_buffer.capacity()<<std::endl;
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
	MutantStack<char> iterable_stack;
	for (char letter = 'a'; letter <= 'z'; letter++)
		iterable_stack.push(letter);
	for (MutantStack<char>::iterator it = iterable_stack.begin(); it != iterable_stack.end(); it++)
	{
		std::cout << *it;
	}
	std::cout << std::endl;

	clock_t	end_time = clock();
	double total_time = double(end_time - start_time) / double(CLOCKS_PER_SEC);
	std::cout << std::endl << "Total execution time : " << std::fixed << total_time  << "sec" << std::endl;
	return (0);
}

#define PAIR	map<int, std::string>::value_type
/*
int	main()
{
	
	//		VECTOR PART
	

	clock_t			vec_start_time = clock();
	vector<int>		vec(10);

	for (int i = 0; i < 10; i++)
		vec[i] = i * 3 + 5;

	std::cout << "Vector content : \n";

	for (vector<int>::iterator it = vec.begin(); it != vec.end(); it++)
		std::cout << *it << " ";
	std::cout << std::endl << std::endl << "Vector first elem : ";
	std::cout << vec.front() << std::endl;
	std::cout << "Vector last elem : ";
	std::cout << vec.back() << std::endl;
	std::cout << "Size : " << vec.size() << " Capacity : " << vec.capacity() << std::endl;

	std::cout << "\nInserting 10000 6 at the front of vector : \n\n";

	vec.insert(vec.begin(), 10000, 6);

	std::cout << "Size : " << vec.size() << " Capacity : " << vec.capacity() << std::endl;

	vector<int>	vec_range(10000, 9);

	std::cout << "\nInserting 10000 9 at the end of vector from an other: \n\n";

	vec.insert(vec.end(), vec_range.begin(), vec_range.end());

	std::cout << "Size : " << vec.size() << " Capacity : " << vec.capacity() << std::endl;

	clock_t	vec_end_time = clock();
	double vec_total_time = double(vec_end_time - vec_start_time) / double(CLOCKS_PER_SEC);
	std::cout << std::endl << "Vector total execution time : " << std::fixed << vec_total_time  << "sec" << std::endl;

	std::cout << "Press a key to continue\n";
	char tmp;
	std::cin >> tmp;

	
	//		MAP PART
	


	clock_t			map_start_time = clock();

	map<int, std::string>	mp;

	mp.insert(PAIR(32, "yes"));
	mp.insert(PAIR(12, "no"));
	mp.insert(PAIR(97, "oui"));
	mp.insert(PAIR(-32, "non"));
	mp.insert(PAIR(2, "si"));
	mp.insert(PAIR(320, "nein"));
	mp.insert(PAIR(41, "niet"));


	clock_t	map_end_time = clock();
	double map_total_time = double(map_end_time - map_start_time) / double(CLOCKS_PER_SEC);
	std::cout << std::endl << "Map total execution time : " << std::fixed << map_total_time  << "sec" << std::endl;

	return (0);
}
*/