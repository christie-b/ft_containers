#include <iostream>
#include <string>
#include <deque>
#include <list>
#include <stack>
#include <vector>
#include <map>
#include <algorithm>
#include "Compare.hpp"
#include "is_integral.hpp"
#include "Iterator_traits.hpp"
#include "Pair.hpp"
#include "random_access_iterator.hpp"
#include "reverse_iterator.hpp"
#include "Stack.hpp"
#include "Vector.hpp"
#include "Map.hpp"

# define RESET  		"\033[0m"
# define BLACK  		"\033[30m"			/* Black */
# define RED    		"\033[31m"			/* Red */
# define GREEN  		"\033[32m"			/* Green */
# define YELLOW 		"\033[33m"			/* Yellow */
# define BLUE   		"\033[34m"			/* Blue */
# define MAGENTA		"\033[35m"			/* Magenta */
# define CYAN   		"\033[36m"			/* Cyan */
# define WHITE  		"\033[37m"			/* White */
# define GREY	  		"\033[90m"			/* Grey */
# define BOLDBLACK  	"\033[1m\033[30m"	/* Bold Black */
# define BOLDRED    	"\033[1m\033[31m"	/* Bold Red */
# define BOLDGREEN  	"\033[1m\033[32m"	/* Bold Green */
# define BOLDYELLOW 	"\033[1m\033[33m"	/* Bold Yellow */
# define BOLDBLUE   	"\033[1m\033[34m"	/* Bold Blue */
# define BOLDMAGENTA	"\033[1m\033[35m"	/* Bold Magenta */
# define BOLDCYAN   	"\033[1m\033[36m"	/* Bold Cyan */
# define BOLDWHITE  	"\033[1m\033[37m"	/* Bold White */

template <typename T>
void PrintStack(std::stack<T> s)
{
	if (s.empty())
		return;

	int x = s.top();
	s.pop();
	PrintStack(s);
	std::cout << x << std::endl;
	s.push(x);
}

template <typename T>
void	printVecInfo(std::vector<T> const &vct, bool print_content = 1)
{
	std::cout << "size: " << vct.size() << std::endl;
	std::cout << "capacity: " << vct.capacity() << std::endl;
	std::cout << "max_size: " << vct.max_size() << std::endl;
	if (print_content)
	{
		typename std::vector<T>::const_iterator it = vct.begin();
		typename std::vector<T>::const_iterator ite = vct.end();
		std::cout << std::endl << "Content is:" << std::endl;
		for (; it != ite; ++it)
			std::cout << "- " << *it << std::endl;
	}
}


// #include <iostream>
// #include <string>
// #include <deque>
// #if 1 //CREATE A REAL STL EXAMPLE
// 	#include <map>
// 	#include <stack>
// 	#include <vector>
// 	namespace ft = std;
// #else
// 	#include <map.hpp>
// 	#include <stack.hpp>
// 	#include <vector.hpp>
// #endif

// #include <stdlib.h>

// #define MAX_RAM 4294967296
// #define BUFFER_SIZE 4096
// struct Buffer
// {
// 	int idx;
// 	char buff[BUFFER_SIZE];
// };


// #define COUNT (MAX_RAM / (int)sizeof(Buffer))

// template<typename T>
// class MutantStack : public std::stack<T>
// {
// public:
// 	MutantStack() {}
// 	MutantStack(const MutantStack<T>& src) { *this = src; }
// 	MutantStack<T>& operator=(const MutantStack<T>& rhs) 
// 	{
// 		this->c = rhs.c;
// 		return *this;
// 	}
// 	~MutantStack() {}

// 	typedef typename std::stack<T>::container_type::iterator iterator;

// 	iterator begin() { return this->c.begin(); }
// 	iterator end() { return this->c.end(); }
// };

// int main(int argc, char** argv) {
// 	if (argc != 2)
// 	{
// 		std::cerr << "Usage: ./test seed" << std::endl;
// 		std::cerr << "Provide a seed please" << std::endl;
// 		std::cerr << "Count value:" << COUNT << std::endl;
// 		return 1;
// 	}
// 	const int seed = atoi(argv[1]);
// 	srand(seed);

// 	std::vector<std::string> vector_str;
// 	std::vector<int> vector_int;
// 	std::stack<int> stack_int;
// 	std::vector<Buffer> vector_buffer;
// 	std::stack<Buffer, std::deque<Buffer> > stack_deq_buffer;
// 	std::map<int, int> map_int;

// 	for (int i = 0; i < COUNT; i++)
// 	{
// 		vector_buffer.push_back(Buffer());
// 	}

// 	for (int i = 0; i < COUNT; i++)
// 	{
// 		const int idx = rand() % COUNT;
// 		vector_buffer[idx].idx = 5;
// 	}
// 	std::vector<Buffer>().swap(vector_buffer);

// 	try
// 	{
// 		for (int i = 0; i < COUNT; i++)
// 		{
// 			const int idx = rand() % COUNT;
// 			vector_buffer.at(idx);
// 			std::cerr << "Error: THIS VECTOR SHOULD BE EMPTY!!" <<std::endl;
// 		}
// 	}
// 	catch(const std::exception& e)
// 	{
// 		//NORMAL ! :P
// 	}
	
// 	for (int i = 0; i < COUNT; ++i)
// 	{
// 		map_int.insert(std::make_pair(rand(), rand()));
// 	}

// 	int sum = 0;
// 	for (int i = 0; i < 10000; i++)
// 	{
// 		int access = rand();
// 		sum += map_int[access];
// 	}
// 	std::cout << "should be constant with the same seed: " << sum << std::endl;

// 	{
// 		std::map<int, int> copy = map_int;
// 	}
// 	MutantStack<char> iterable_stack;
// 	for (char letter = 'a'; letter <= 'z'; letter++)
// 		iterable_stack.push(letter);
// 	for (MutantStack<char>::iterator it = iterable_stack.begin(); it != iterable_stack.end(); it++)
// 	{
// 		std::cout << *it;
// 	}
// 	std::cout << std::endl;
// 	return (0);
// }

int main()
{
	std::cout << BOLDBLUE << "****** STACK TESTS ******" << RESET << std::endl;
	std::cout << BOLDCYAN << "Constructors tests" << RESET << std::endl;
	{
		std::stack<int>	stack1;
		std::stack<int>	stack2(stack1);

		if (stack1.size() != 0 || !stack1.empty())
			std::cout << RED << "Default constructor:\t KO" << RESET << std::endl;
		else
			std::cout << GREEN << "Default constructor:\t OK" << RESET << std::endl;

		if (stack2.size() != 0 || !stack2.empty())
			std::cout << RED << "Copy constructor:\t KO" << RESET << std::endl;
		else
			std::cout << GREEN << "Copy constructor:\t OK" << RESET << std::endl;
	}
	std::cout << std::endl << BOLDCYAN << "Assignment Operator test" << RESET << std::endl;
	{
		std::stack<int>	stack1;
		stack1.push(42);
		stack1.push(84);
		std::stack<int>	stack2 = stack1;
		if (stack1.size() != 2 || stack1.empty()
			|| stack2.size() != 2 || stack2.empty())
			std::cout << RED << "Assignment operator:\t KO" << RESET << std::endl;
		else
			std::cout << GREEN << "Assignment operator:\t OK" << RESET << std::endl;
		std::cout << "Stack1:" << std::endl;
		PrintStack(stack1);
		std::cout << "Stack2:" << std::endl;
		PrintStack(stack2);
	}

	std::cout << std::endl << BOLDCYAN << "Empty test" << RESET << std::endl;
	{
		std::stack<int>	stack1;
		std::cout << "is empty? " << stack1.empty() << std::endl;
		std::cout << GREY << "Pushing a number..." << RESET << std::endl;
		stack1.push(42);
		std::cout << "is empty? " << stack1.empty() << std::endl;
	}
	std::cout << std::endl << BOLDCYAN << "Size / Top / Push / Pop test" << RESET << std::endl;
	{
		std::stack<int>	stack1;
		std::cout << "Size: " << stack1.size() << std::endl;
		std::cout << GREY << "Pushing a number..." << RESET << std::endl;
		stack1.push(42);
		std::cout << "Size: " << stack1.size() << std::endl;
		PrintStack(stack1);
		std::cout << GREY << "Pushing 2 numbers..." << RESET << std::endl;
		stack1.push(84);
		stack1.push(99);
		std::cout << "Size: " << stack1.size() << std::endl;
		PrintStack(stack1);
		std::cout << "Top: " << stack1.top() << std::endl;
		std::cout << GREY << "Poping a number..." << RESET << std::endl;
		stack1.pop();
		std::cout << "Size: " << stack1.size() << std::endl;
		PrintStack(stack1);
		std::cout << "Top: " << stack1.top() << std::endl;
	}
	std::cout << std::endl << BOLDCYAN << "Relational Operators test" << RESET << std::endl;
	{
		std::stack<int>	 stack1;
		std::stack<int>	 stack2;

		if (stack1 != stack2)
			std::cout << RED << "Operator !=\t KO" << RESET << std::endl;
		else
			std::cout << GREEN << "Operator !=\t OK" << RESET << std::endl;

		if (!(stack1 == stack2))
			std::cout << RED << "Operator ==\t KO" << RESET << std::endl;
		else
			std::cout << GREEN << "Operator ==\t OK" << RESET << std::endl;

		stack1.push(42);
		stack2.push(84);
		if (stack2 > stack1)
			std::cout << GREEN << "Operator >\t OK" << RESET << std::endl;
		else
			std::cout << RED << "Operator >\t KO" << RESET << std::endl;

		if (stack2 >= stack1)
			std::cout << GREEN << "Operator >=\t OK" << RESET << std::endl;
		else
			std::cout << RED << "Operator >=\t KO" << RESET << std::endl;

		if (stack1 < stack2)
			std::cout << GREEN << "Operator <\t OK" << RESET << std::endl;
		else
			std::cout << RED << "Operator <\t KO" << RESET << std::endl;

		if (stack1 <= stack2)
			std::cout << GREEN << "Operator <=\t OK" << RESET << std::endl;
		else
			std::cout << RED << "Operator <=\t KO" << RESET << std::endl;
	}
	std::cout << std::endl << BOLDBLUE << "****** VECTOR TESTS ******" << RESET << std::endl;
	std::cout << BOLDCYAN << "Constructors tests" << RESET << std::endl;
	{
		std::vector<int> vector1;
		std::vector<int> vector2;
		if (vector1.size() != 0 || vector1.capacity() != 0)
			std::cout << RED << "Default Constructor\t KO" << RESET << std::endl;
		if (vector2.size() != vector1.size() || vector2.capacity() != vector1.capacity())
			std::cout << RED << "Default Constructor\t KO" << RESET << std::endl;
		std::cout << GREEN << "Default Constructor\t OK" << RESET << std::endl;
	}
	{
		std::vector<int> vector1(1);
		std::vector<int> vector2(1);
		bool fill = 0;
		if (vector1.size() != vector2.size() || vector1.capacity() != vector2.capacity())
			fill = 1;

		std::vector<int> vector3(3, 42);
		std::vector<int> vector4(3, 42);
		if (vector3.size() != vector4.size() || vector3.capacity() != vector4.capacity())
			fill = 1;
		for (size_t i = 0; i < vector3.size(); i++)
		{
			if (vector3[i] != vector4[i])
				fill = 1;
		}

		std::vector<int> vector5(10, 42);
		std::vector<int> vector6(10, 42);
		if (vector5.size() != vector6.size() || vector5.capacity() != vector6.capacity())
			fill = 1;
		for (size_t i = 0; i < vector5.size(); i++)
		{
			if (vector5[i] != vector6[i])
				fill = 1;
		}
		if (fill == 1)
			std::cout << RED << "Fill Constructor\t KO" << RESET << std::endl;
		else
			std::cout << GREEN << "Fill Constructor\t OK" << RESET << std::endl;
	}
	{
		std::vector<int> vector1(5, 42);
		std::vector<int> vector2(5, 42);
		int	range = 0;

		std::vector<int> vec1(vector1.begin(), vector1.end());
		std::vector<int> vec2(vector2.begin(), vector2.end());
		if (vec1.size() != vec2.size() || vec1.capacity() != vec2.capacity())
			range = 1;
		for (size_t i = 0; i < vec1.size(); i++)
			if (vec1[i] != vec2[i])
				range = 1;
		if (range == 1)
			std::cout << RED << "Range Constructor\t KO" << RESET << std::endl;
		else
			std::cout << GREEN << "Range Constructor\t OK" << RESET << std::endl;
	}
	{
		std::vector<int> vector1(5, 42);
		std::vector<int> vector2(5, 42);
		int	copy = 0;

		std::vector<int> vec1(vector1);
		std::vector<int> vec2(vector2);

		if (vec1.size() != vec2.size() || vec1.size() != vector1.size()
			|| vec1.capacity() != vec2.capacity() || vec1.capacity() != vector1.capacity())
			copy = 1;
		for (size_t i = 0; i < vec1.size(); i++)
			if (vec1[i] != vec2[i])
				copy = 1;
		if (copy == 1)
			std::cout << RED << "Copy Constructor\t KO" << RESET << std::endl;
		else
			std::cout << GREEN << "Copy Constructor\t OK" << RESET << std::endl;
	}
	std::cout << std::endl << BOLDCYAN << "Assignment Operator test" << RESET << std::endl;
	{
		std::vector<int> vector1(5, 42);
		std::vector<int> vector2(5, 42);
		int assign = 0;

		std::vector<int> vec1 = vector1;
		std::vector<int> vec2 = vector2;

		if (vec1.size() != vec2.size() || vec1.capacity() != vec2.capacity())
			assign = 1;

		for (size_t i = 0; i < vec1.size(); i++)
			if (vec1[i] != vec2[i])
				assign = 1;
		if (assign == 1)
			std::cout << RED << "Assignment Operator =\t KO" << RESET << std::endl;
		else
			std::cout << GREEN << "Assignment Operator =\t OK" << RESET << std::endl;
	}
	std::cout << std::endl << BOLDCYAN << "Begin(), End() test through iteration" << RESET << std::endl;
	{
		std::vector<int> vec;
		std::cout << GREY << "Pushing 5 numbers (42, 11, 84, 99, 77)... " << RESET << std::endl;
		vec.push_back(42);
		vec.push_back(11);
		vec.push_back(84);
		vec.push_back(99);
		vec.push_back(7);
		std::cout << GREY << "Iterating in the vector... " << RESET << std::endl;
		for (std::vector<int>::iterator it = vec.begin(); it != vec.end(); it++)
			std::cout << *it << std::endl;
	}
	std::cout << std::endl << BOLDCYAN << "Rbegin(), Rend() test through iteration" << RESET << std::endl;
	{
		std::vector<int> vec;
		std::cout << GREY << "Pushing 5 numbers (42, 11, 84, 99, 77)... " << RESET << std::endl;
		vec.push_back(42);
		vec.push_back(11);
		vec.push_back(84);
		vec.push_back(99);
		vec.push_back(7);
		std::cout << GREY << "Iterating in the vector... " << RESET << std::endl;
		for (std::vector<int>::reverse_iterator rit = vec.rbegin(); rit != vec.rend(); rit++)
			std::cout << *rit << std::endl;
	}
	std::cout << std::endl << BOLDCYAN << "Size test" << RESET << std::endl;
	{
		std::cout << GREY << "Pushing 5 numbers..." << RESET << std::endl;
		std::vector<int> vec1;
		vec1.push_back(42);
		vec1.push_back(11);
		vec1.push_back(84);
		vec1.push_back(99);
		vec1.push_back(7);
		std::cout << "vec1 size: " << vec1.size() << std::endl;

		std::cout << GREY << "Initializing a vector with 10 elements..." << RESET << std::endl;
		std::vector<int> vec2(10, 42);
		std::cout << "vec2 size: " << vec2.size() << std::endl;
	}
	std::cout << std::endl << BOLDCYAN << "Max_size test" << RESET << std::endl;
	{
		std::vector<int> vec1;
		std::cout << "vec1 max_size: " << vec1.max_size() << std::endl;
		std::cout << GREY << "Pushing 5 numbers..." << RESET << std::endl;
		vec1.push_back(42);
		vec1.push_back(11);
		vec1.push_back(84);
		vec1.push_back(99);
		vec1.push_back(7);
		std::cout << "vec1 max_size after push_back: " << vec1.max_size() << std::endl;

		std::cout << GREY << "Initializing a vector with 10 elements..." << RESET << std::endl;
		std::vector<int> vec2(10, 42);
		std::cout << "vec2 max_size: " << vec2.max_size() << std::endl;
	}
	std::cout << std::endl << BOLDCYAN << "Resize test" << RESET << std::endl;
	{
		std::vector<int> vec;

		for (std::vector<int>::size_type i = 1; i < 10; i++)
			vec.push_back(i);
		std::cout << BLUE << "Initial Content: \n" << RESET;
		std::cout << "Size: " << vec.size() << std::endl;
		for (std::vector<int>::size_type i = 0; i < vec.size(); i++)
			std::cout << vec[i] << std::endl;

		vec.resize(5);
		std::cout << BLUE << "\nAfter resize(5): \n" << RESET;
		std::cout << "Size: " << vec.size() << std::endl;
		for (std::vector<int>::size_type i = 0; i < vec.size(); i++)
			std::cout << vec[i] << std::endl;
		vec.resize(8,100);
		std::cout << BLUE << "\nAfter resize(8, 100): \n" << RESET;
		std::cout << "Size: " << vec.size() << std::endl;
		for (std::vector<int>::size_type i = 0; i < vec.size(); i++)
			std::cout << vec[i] << std::endl;
		vec.resize(12);
		std::cout << BLUE << "\nAfter resize(12): \n" << RESET;
		std::cout << "Size: " << vec.size() << std::endl;
		for (std::vector<int>::size_type i = 0; i < vec.size(); i++)
			std::cout << vec[i] << std::endl;
	}
	std::cout << std::endl << BOLDCYAN << "Capacity test" << RESET << std::endl;
	{
		std::vector<int> vec1;
		std::cout << GREY << "Pushing 100 elements..." << RESET << std::endl;
		for (int i = 0; i < 100; i++)
			vec1.push_back(i);
		std::cout << "vec1 capacity: " << vec1.capacity() << std::endl;
		std::cout << GREY << "Initializing a vector with 10 elements..." << RESET << std::endl;
		std::vector<int> vec2(10, 42);
		std::cout << "vec2 capacity: " << vec2.capacity() << std::endl;
	}
	std::cout << std::endl << BOLDCYAN << "Empty test" << RESET << std::endl;
	{
		std::vector<int> vec1;
		std::cout << "vec1 empty ? " << vec1.empty() << std::endl;
		std::vector<int> vec2(10, 42);
		std::cout << "vec2(10,42) empty ? " << vec2.empty() << std::endl;
	}
	std::cout << std::endl << BOLDCYAN << "Reserve test" << RESET << std::endl;
	{
		std::vector<int> vec1;
		std::cout << "vec1 size : " << vec1.size() << std::endl;
		std::cout << "vec1 capacity " << vec1.capacity() << std::endl;
		std::cout << GREY << "Reserve(10)" << RESET << std::endl;
		vec1.reserve(10);
		std::cout << "vec1 size after reserve(10) : " << vec1.size() << std::endl;
		std::cout << "vec1 capacity after reserve(10) : " << vec1.capacity() << std::endl;
		std::cout << GREY << "Initializing a vector with 10 elements..." << RESET << std::endl;
		std::vector<int> vec2(10, 42);
		std::cout << "vec2(10,42) size : " << vec2.size() << std::endl;
		std::cout << "vec2(10,42) capacity : " << vec2.capacity() << std::endl;
		std::cout << GREY << "Reserve(100)" << RESET << std::endl;
		vec2.reserve(100);
		std::cout << "vec2(10,42) size after reserve(100) : " << vec2.size() << std::endl;
		std::cout << "vec2(10,42) capacity after reserve(100) : " << vec2.capacity() << std::endl;
		std::cout << GREY << "Popping back..." << RESET << std::endl;
		vec2.pop_back();
		std::cout << "vec2(10,42) size after pop_back() : " << vec2.size() << std::endl;
		std::cout << "vec2(10,42) capacity after pop_back() : " << vec2.capacity() << std::endl;
	}
	std::cout << std::endl << BOLDCYAN << "Operator[] test" << RESET << std::endl;
	{
		std::vector<int> vec;
		std::cout << GREY << "Pushing 10 elements..." << RESET << std::endl;
		for (size_t i = 0; i < 10; i++)
			vec.push_back(i);
		std::cout << GREY << "Accessing the elements of the vector through [index]..." << RESET << std::endl;
		for (size_t i = 0; i < 10; i++)
			std::cout << vec[i] << " ";
		std::cout << std::endl;
	}
	std::cout << std::endl << BOLDCYAN << "At test" << RESET << std::endl;
	{
		std::vector<int> vec;
		std::cout << GREY << "Pushing 10 elements..." << RESET << std::endl;
		for (size_t i = 0; i < 10; i++)
			vec.push_back(i);
		std::cout << GREY << "Accessing the elements of the vector through at(index)..." << RESET << std::endl;
		for (size_t i = 0; i < 10; i++)
			std::cout << vec.at(i) << " ";
		std::cout << std::endl;
	}
	std::cout << std::endl << BOLDCYAN << "Front test" << RESET << std::endl;
	{
		std::vector<int> vec;
		std::cout << GREY << "Pushing 10 elements from 0 to 9..." << RESET << std::endl;
		for (size_t i = 0; i < 10; i++)
			vec.push_back(i);
		std::cout << vec.front() << std::endl;
	}
	std::cout << std::endl << BOLDCYAN << "Back test" << RESET << std::endl;
	{
		std::vector<int> vec;
		for (size_t i = 0; i < 10; i++)
			vec.push_back(i);
		std::cout << vec.back() << std::endl;
	}
	std::cout << std::endl << BOLDCYAN << "Assign test" << RESET << std::endl;
	{
		std::vector<int> vec;
		std::cout << "vec size : " << vec.size() << std::endl;
		vec.assign(5, 42);
		std::cout << "vec size after assign(5, 42) : " << vec.size() << std::endl;
		std::cout << "vec content : " << std::endl;
		for (size_t i = 0; i < vec.size(); i++)
			std::cout << vec[i] << " ";
		std::cout << std::endl;
	}
	std::cout << std::endl << BOLDCYAN << "Push Back test" << RESET << std::endl;
	{
		std::vector<int> vec;
		std::cout << "vec size : " << vec.size() << std::endl;
		std::cout << GREY << "Pushing 10 elements from 0 to 9..." << RESET << std::endl;
		for (size_t i = 0; i < 10; i++)
			vec.push_back(i);
		std::cout << "vec size after push_back : " << vec.size() << std::endl;
		std::cout << "vec content : " << std::endl;
		for (size_t i = 0; i < vec.size(); i++)
			std::cout << vec[i] << " ";
		std::cout << std::endl;
	}
	std::cout << std::endl << BOLDCYAN << "Pop Back test" << RESET << std::endl;
	{
		std::vector<int> vec;
		std::cout << "vec size : " << vec.size() << std::endl;
		std::cout << GREY << "Pushing 10 elements from 0 to 9..." << RESET << std::endl;
		for (size_t i = 0; i < 10; i++)
			vec.push_back(i);
		std::cout << "vec size after push_back : " << vec.size() << std::endl;
		std::cout << "vec content : " << std::endl;
		for (size_t i = 0; i < vec.size(); i++)
			std::cout << vec[i] << " ";
		std::cout << std::endl;
		std::cout << GREY << "Popping back..." << RESET << std::endl;
		vec.pop_back();
		std::cout << "vec size after pop_back : " << vec.size() << std::endl;
		std::cout << "vec content : " << std::endl;
		for (size_t i = 0; i < vec.size(); i++)
			std::cout << vec[i] << " ";
		std::cout << std::endl;
	}
	std::cout << std::endl << BOLDCYAN << "Insert tests" << RESET << std::endl;
	{
		// Single element
		std::cout << BLUE << "Single element: \n" << RESET;
		std::vector<int> vec1;
		std::cout << GREY << "Pushing 5 elements..." << RESET << std::endl;
		for (int i = 0; i < 5; i++)
			vec1.push_back(i);
		printVecInfo(vec1);
		std::cout << std::endl;
		std::cout << GREY << "Inserting 42 at the end..." << RESET << std::endl;
		vec1.insert(vec1.end(), 42);
		std::cout << "After insert: " << std::endl;
		printVecInfo(vec1);
		std::cout << std::endl;

		// Fill
		std::cout << BLUE << "Fill: \n" << RESET;
		std::cout << GREY << "Inserting at index 5, 3 x 99..." << RESET << std::endl;
		vec1.insert(vec1.begin() + 5, 3, 99);
		printVecInfo(vec1);
		std::cout << std::endl;

		// Range
		std::cout << BLUE << "Range: \n" << RESET;
		std::cout << GREY << "Resizing to 5..." << RESET << std::endl;
		vec1.resize(5);
		std::vector<int> vec2(2, 65);
		std::cout << GREY << "Inserting at index 3, 2 x 65..." << RESET << std::endl;
		vec1.insert(vec1.begin() + 3, vec2.begin(), vec2.end());
		printVecInfo(vec1);
	}
	std::cout << std::endl << BOLDCYAN << "Erase tests" << RESET << std::endl;
	{
		std::cout << BLUE << "Position: \n" << RESET;
		std::vector<int> vec;

		std::cout << GREY << "Pushing 10 elements..." << RESET << std::endl;
		for (int i = 0; i < 10; i++)
			vec.push_back(i);
		printVecInfo(vec);
		std::cout << std::endl;

		// erase the 6th element
		std::cout << GREY << "Erasing the 6th element..." << RESET << std::endl;
		vec.erase (vec.begin() + 5);
		std::cout << "After erase:" << std::endl;
		printVecInfo(vec);
		std::cout << std::endl;

		std::cout << BLUE << "Range: \n" << RESET;
		std::vector<int> vec2;

		std::cout << GREY << "Pushing 10 elements..." << RESET << std::endl;
		for (int i = 0; i < 10; i++)
			vec2.push_back(i);
		printVecInfo(vec2);
		std::cout << std::endl;

		// erase the first 3 elements:
		std::cout << GREY << "Erasing the first 3 elements..." << RESET << std::endl;
		vec2.erase (vec2.begin(),vec2.begin() + 3);
		std::cout << "After erase:" << std::endl;
		printVecInfo(vec2);
	}
	std::cout << std::endl << BOLDCYAN << "Swap test" << RESET << std::endl;
	{
		std::vector<int> vec1(3, 42);
		std::vector<int> vec2(5, 84);
		std::cout << BLUE << "Vec1: \n" << RESET;
		std::vector<int>::iterator it1 = vec1.begin();
		std::vector<int>::iterator it2 = vec2.begin();
		printVecInfo(vec1);
		std::cout << BLUE << "\nVec2: \n" << RESET;
		printVecInfo(vec2);
		std::cout << "it1 before swap: " << *it1 << std::endl;
		std::cout << "it2 before swap: " << *it2 << std::endl;

		vec1.swap(vec2);
		std::cout << std::endl << "After swap: " << std::endl;
		std::cout << BLUE << "\nVec1: \n" << RESET;
		printVecInfo(vec1);
		std::cout << BLUE << "\nVec2: \n" << RESET;
		printVecInfo(vec2);
		std::cout << "it1 after swap: " << *it1 << std::endl;
		std::cout << "it2 after swap: " << *it2 << std::endl;
	}
	std::cout << std::endl << BOLDCYAN << "Clear test" << RESET << std::endl;
	{
		std::vector<int> vec1(3, 42);
		printVecInfo(vec1);
		std::cout << GREY << "Clearing the vector..." << RESET << std::endl;
		vec1.clear();
		std::cout << std::endl << "After clear(): " << std::endl;
		printVecInfo(vec1);
	}
	std::cout << std::endl << BOLDCYAN << "Relational Operators test" << RESET << std::endl;
	{
		std::cout << GREY << "Creating vec1, with three 100" << RESET << std::endl;
		std::vector<int> vec1 (3,100);   // three ints with a value of 100
		std::cout << GREY << "Creating vec2, with two 200" << RESET << std::endl;
		std::vector<int> vec2 (2,200);   // two ints with a value of 200
		if (vec1 == vec2) std::cout << "vec1 and vec2 are equal" << std::endl;
		if (vec1 != vec2) std::cout << "vec1 and vec2 are not equal" << std::endl;
		if (vec1 < vec2) std::cout << "vec1 is less than vec2" << std::endl;
		if (vec1 > vec2) std::cout << "vec1 is greater than vec2" << std::endl;
		if (vec1 <= vec2) std::cout << "vec1 is less than or equal to vec2" << std::endl;
		if (vec1 >= vec2) std::cout << "vec1 is greater than or equal to vec2" << std::endl;
	}
	std::cout << std::endl << BOLDCYAN << "Non Member Swap test" << RESET << std::endl;
	{
		std::vector<std::string> vec1(3, "abc");
		std::vector<std::string> vec2(5, "xyz");
		std::cout << BLUE << "Vec1: \n" << RESET;
		printVecInfo(vec1);
		std::cout << BLUE << "\nVec2: \n" << RESET;
		printVecInfo(vec2);

		vec1.swap(vec2);
		std::cout << std::endl << "After swap: " << std::endl;
		std::cout << BLUE << "\nVec1: \n" << RESET;
		printVecInfo(vec1);
		std::cout << BLUE << "\nVec2: \n" << RESET;
		printVecInfo(vec2);
	}
	std::cout << std::endl << BOLDBLUE << "****** MAP TESTS ******" << RESET << std::endl;
	std::cout << BOLDCYAN << "Constructors tests" << RESET << std::endl;
	{
		std::map<int, int> map1;
		std::map<int, int> map2;
		if (map1.size() != 0)
			std::cout << RED << "Default Constructor\t KO" << RESET << std::endl;
		if (map2.size() != map1.size())
			std::cout << RED << "Default Constructor\t KO" << RESET << std::endl;
		std::cout << GREEN << "Default Constructor\t OK" << RESET << std::endl;
	}
	{
		std::map<int, char> map1;
		map1[0] = 'a';
		map1[1] = 'b';
		map1[2] = 'c';
		map1[3] = 'd';
		map1[4] = 'e';

		std::map<int, char> map2(map1.begin(), map1.end());
		if (map2.size() != 5 || map2.empty())
			std::cout << RED << "Range Constructor\t KO" << RESET << std::endl;
		else if (map2[0] != 'a' || map2[1] != 'b' || map2[2] != 'c' || map2[3] != 'd'
				|| map2[4] != 'e')
			std::cout << RED << "Range Constructor\t KO" << RESET << std::endl;
		else
			std::cout << GREEN << "Range Constructor\t OK" << RESET << std::endl;
	}
	{
		std::map<int, char> map1;
		map1[0] = 'a';
		map1[1] = 'b';
		map1[2] = 'c';
		map1[3] = 'd';
		map1[4] = 'e';

		std::map<int, char> map2(map1);
		if (map2.size() != 5 || map2.empty())
			std::cout << RED << "Copy Constructor\t KO" << RESET << std::endl;
		else if (map2[0] != 'a' || map2[1] != 'b' || map2[2] != 'c' || map2[3] != 'd'
				|| map2[4] != 'e')
			std::cout << RED << "Copy Constructor\t KO" << RESET << std::endl;
		else
			std::cout << GREEN << "Copy Constructor\t OK" << RESET << std::endl;
	}
	std::cout << std::endl << BOLDCYAN << "Assignment Operator test" << RESET << std::endl;
	{
		std::map<int, char> map1;
		map1[0] = 'a';
		map1[1] = 'b';
		map1[2] = 'c';

		std::map<int, char> map2 = map1;
		if (map2.size() != 3 || map2.empty())
			std::cout << RED << "Assignment Operator\t KO" << RESET << std::endl;
		else if (map2[0] != 'a' || map2[1] != 'b' || map2[2] != 'c')
			std::cout << RED << "Assignment Operator\t KO" << RESET << std::endl;
		else
			std::cout << GREEN << "Assignment Operator\t OK" << RESET << std::endl;
	}
	std::cout << std::endl << BOLDCYAN << "Begin() / End() test through iteration" << RESET << std::endl;
	{
		std::map<int, char> map1;
		map1[0] = 'a';
		map1[1] = 'b';
		map1[2] = 'c';
		map1[3] = 'd';
		map1[4] = 'e';
		std::map<int, char>::iterator it = map1.begin();
		std::map<int, char>::iterator ite = map1.end();
		while (it != ite)
		{
			std::cout << it->second << std::endl;
			it++;
		}
	}
	std::cout << std::endl << BOLDCYAN << "Rbegin() / Rend() test through iteration" << RESET << std::endl;
	{
		std::map<int, char> map1;
		map1[0] = 'a';
		map1[1] = 'b';
		map1[2] = 'c';
		map1[3] = 'd';
		map1[4] = 'e';
		std::map<int, char>::reverse_iterator rit = map1.rbegin();
		std::map<int, char>::reverse_iterator rite = map1.rend();
		while (rit != rite)
		{
			std::cout << rit->second << std::endl;
			rit++;
		}
	}
	std::cout << std::endl << BOLDCYAN << "Empty() test" << RESET << std::endl;
	{
		std::map<int, char> map1;
		std::cout << "Map empty() : " << map1.empty() << std::endl;
		std::cout << "Map size : " << map1.size() << std::endl;
		map1[0] = 'a';
		std::cout << std::endl << GREY << "Adding value 'a'... " << RESET << std::endl;
		std::cout << "Map empty() after adding a value : " << map1.empty() << std::endl;
		std::cout << "Map size : " << map1.size() << std::endl;
	}
	std::cout << std::endl << BOLDCYAN << "Size test" << RESET << std::endl;
	{
		std::map<int, char> map1;
		std::cout << "Map size : " << map1.size() << std::endl;
		map1[0] = 'a';
		std::cout << std::endl << GREY << "Adding value 'a'... " << RESET << std::endl;
		std::cout << "Map size after adding a value : " << map1.size() << std::endl;
		map1[1] = 'b';
		std::cout << std::endl << GREY << "Adding value 'b'... " << RESET << std::endl;
		std::cout << "Map size after adding a value : " << map1.size() << std::endl;
		map1[2] = 'c';
		std::cout << std::endl << GREY << "Adding value 'c'... " << RESET << std::endl;
		std::cout << "Map size after adding a value : " << map1.size() << std::endl;
	}
	std::cout << std::endl << BOLDCYAN << "Max_size test" << RESET << std::endl;
	{
		std::map<int, char> map1;
		std::map<int, char> map2;

		if ( map1.max_size() != map2.max_size())
			std::cout << RED << "Max_size\t KO" << RESET << std::endl;
		else
			std::cout << GREEN << "Max_size\t OK" << RESET << std::endl;
	}
	std::cout << std::endl << BOLDCYAN << "Access Operator test" << RESET << std::endl;
	{
		std::map<int, char> map1;
		map1[0] = 'a';
		map1[1] = 'b';
		map1[2] = 'c';
		std::cout << "map[0] content : " << map1[0] << std::endl;
		std::cout << "map[1] content : " << map1[1] << std::endl;
		std::cout << "map[2] content : " << map1[2] << std::endl;
	}
	std::cout << std::endl << BOLDCYAN << "Insert tests" << RESET << std::endl;
	{
		std::cout << BLUE << "Single Element : " << RESET << std::endl;
		std::map<int, char> map1;

		map1.insert(std::make_pair<int, char>(0, 'a'));
		map1.insert(std::make_pair<int, char>(1, 'b'));
		map1.insert(std::make_pair<int, char>(2, 'c'));
		std::cout << std::endl << GREY << "Inserting 3 pairs, a, b and c... " << RESET << std::endl;
		std::cout << "map1[0] content : " << map1[0] << std::endl;
		std::cout << "map1[1] content : " << map1[1] << std::endl;
		std::cout << "map1[2] content : " << map1[2] << std::endl;

		std::cout << std::endl << BLUE << "Hint : " << RESET << std::endl;
		std::map<int, char> map2;

		map2.insert(std::make_pair<int, char>(0, 'a'));
		map2.insert(std::make_pair<int, char>(2, 'c'));
		map2.insert(std::make_pair<int, char>(3, 'd'));
		std::cout << std::endl << GREY << "Inserting 3 pairs, a, c and d... " << RESET << std::endl;

		std::cout << "map2[0] content : " << map2[0] << std::endl;
		std::cout << "map2[2] content : " << map2[2] << std::endl;
		std::cout << "map2[3] content : " << map2[3] << std::endl;

		std::map<int, char>::iterator it = map2.begin()++;
		map2.insert(it, std::make_pair<int, char>(1, 'b'));
		std::cout << std::endl << GREY << "Inserting pair(1, 'b')... " << RESET << std::endl;
		std::cout << "\nAfter insert : " << std::endl;
		std::cout << "map2[0] content : " << map2[0] << std::endl;
		std::cout << "map2[1] content : " << map2[1] << std::endl;
		std::cout << "map2[2] content : " << map2[2] << std::endl;
		std::cout << "map2[3] content : " << map2[3] << std::endl;

		std::cout << std::endl << BLUE << "Range : " << RESET << std::endl;
		std::map<int, char> map3;
		std::cout << "map3 size : " << map3.size() << std::endl;
		map3.insert(map2.begin(), map2.find(2));
		std::cout << std::endl << GREY << "Inserting map2 values from 0 to 2 excl... " << RESET << std::endl;
		std::cout << "map3 size after insert : " << map3.size() << std::endl;
		std::cout << "map3[0] content : " << map3[0] << std::endl;
		std::cout << "map3[1] content : " << map3[1] << std::endl;
	}
	std::cout << std::endl << BOLDCYAN << "Erase tests" << RESET << std::endl;
	{
		std::cout << std::endl << BLUE << "Single Element : " << RESET << std::endl;
		std::map<int, char> map1;
		map1[0] = 'a';
		map1[1] = 'b';
		map1[2] = 'c';
		map1[3] = 'd';
		map1[4] = 'e';

		std::map<int, char>::iterator it;
		it = map1.find(1);
		std::cout << "map size : " << map1.size() << std::endl;
		std::cout << "map1[0] content : " << map1[0] << std::endl;
		std::cout << "map1[1] content : " << map1[1] << std::endl;
		std::cout << "map1[2] content : " << map1[2] << std::endl;
		std::cout << "map1[3] content : " << map1[3] << std::endl;
		std::cout << "map1[4] content : " << map1[4] << std::endl;
		map1.erase(it); // delete b
		std::cout << std::endl << GREY << "Erasing b... " << RESET << std::endl;
		std::cout << "map size after erase : " << map1.size() << std::endl;
		std::cout << "map1[0] content : " << map1[0] << std::endl;
		std::cout << "map1[2] content : " << map1[2] << std::endl;
		std::cout << "map1[3] content : " << map1[3] << std::endl;
		std::cout << "map1[4] content : " << map1[4] << std::endl;

		std::cout << std::endl << BLUE << "Erase with key : " << RESET << std::endl;
		std::cout << "map size : " << map1.size() << std::endl;
		map1.erase(3); // delete d
		std::cout << std::endl << GREY << "Erasing d... " << RESET << std::endl;
		std::cout << "map size after erase : " << map1.size() << std::endl;
		std::cout << "map1[0] content : " << map1[0] << std::endl;
		std::cout << "map1[2] content : " << map1[2] << std::endl;
		std::cout << "map1[4] content : " << map1[4] << std::endl;

		std::cout << std::endl << BLUE << "Range : " << RESET << std::endl;
		std::cout << "map size : " << map1.size() << std::endl;
		it = map1.find(2);
		map1.erase(it, map1.end()); // delete c and e
		std::cout << std::endl << GREY << "Erasing c and e... " << RESET << std::endl;
		std::cout << "map size after erase : " << map1.size() << std::endl;
		std::cout << "map2[0] content : " << map1[0] << std::endl;
	}
	std::cout << std::endl << BOLDCYAN << "Swap test" << RESET << std::endl;
	{
		std::map<int, char> map1;
		std::map<int, char> map2;

		map1[0] = 'a';
		map1[1] = 'b';
		map1[2] = 'c';

		map2[0] = 'y';
		map2[1] = 'z';
		std::cout << "map1 size : " << map1.size() << std::endl;
		std::cout << "map1[0] content : " << map1[0] << std::endl;
		std::cout << "map1[1] content : " << map1[1] << std::endl;
		std::cout << "map1[2] content : " << map1[2] << std::endl;
		std::cout << "map2 size : " << map2.size() << std::endl;
		std::cout << "map2[0] content : " << map2[0] << std::endl;
		std::cout << "map2[1] content : " << map2[1] << std::endl;

		std::cout << std::endl << GREY << "Swapping map1 and map2... " << RESET << std::endl;
		map1.swap(map2);
		std::cout << "map1 size : " << map1.size() << std::endl;
		std::cout << "map1[0] content : " << map1[0] << std::endl;
		std::cout << "map1[1] content : " << map1[1] << std::endl;
		std::cout << "map2 size : " << map2.size() << std::endl;
		std::cout << "map2[0] content : " << map2[0] << std::endl;
		std::cout << "map2[1] content : " << map2[1] << std::endl;
		std::cout << "map2[2] content : " << map2[2] << std::endl;
	}
	std::cout << std::endl << BOLDCYAN << "Clear test" << RESET << std::endl;
	{
		std::map<int, char> map1;

		map1[0] = 'a';
		map1[1] = 'b';
		map1[2] = 'c';
		std::cout << "map1 size : " << map1.size() << std::endl;
		std::cout << "map1[0] content : " << map1[0] << std::endl;
		std::cout << "map1[1] content : " << map1[1] << std::endl;
		std::cout << "map1[2] content : " << map1[2] << std::endl;
	
		map1.clear();
		std::cout << std::endl << GREY << "Clearing map1... " << RESET << std::endl;
		std::cout << "map1 size after clear() : " << map1.size() << std::endl;
		std::cout << std::endl << GREY << "Adding 2 values to map1... " << RESET << std::endl;
		map1[0] = 'y';
		map1[1] = 'z';
		std::cout << "map1 size after adding y and z : " << map1.size() << std::endl;
		std::cout << "map1[0] content : " << map1[0] << std::endl;
		std::cout << "map1[1] content : " << map1[1] << std::endl;
	}
	std::cout << std::endl << BOLDCYAN << "Key_comp test" << RESET << std::endl;
	{
		std::map<char,int> map1;

		std::map<char,int>::key_compare mycomp = map1.key_comp();

		map1['a'] = 100;
		map1['b'] = 200;
		map1['c'] = 300;

		std::cout << "map1 contains:\n";

		char highest = map1.rbegin()->first;     // key value of last element

		std::map<char,int>::iterator it = map1.begin();
		do
		{
			std::cout << it->first << " => " << it->second << std::endl;
		} while (mycomp((*it++).first, highest) );

		std::cout << "mycomp('a', 'b') : " << mycomp('a', 'b') << std::endl; //should be true
		std::cout << "mycomp('b', 'a') : " << mycomp('b', 'a') << std::endl; //should be false
		std::cout << "mycomp('a', 'a') : " << mycomp('a', 'a') << std::endl; //should be false
	}
	std::cout << std::endl << BOLDCYAN << "value_comp test" << RESET << std::endl;
	{
		std::map<char,int> map1;

		map1['x'] = 1001;
		map1['y'] = 2002;
		map1['z'] = 3003;

		std::cout << "map1 contains:\n";

		std::pair<char,int> highest = *map1.rbegin();          // last element

		std::map<char,int>::iterator it = map1.begin();
		do
		{
			std::cout << it->first << " => " << it->second << std::endl;
		} while ( map1.value_comp()(*it++, highest) );
	}
	std::cout << std::endl << BOLDCYAN << "Find test" << RESET << std::endl;
	{
		std::map<char,int> map1;
		std::map<char,int>::iterator it;

		map1['a']=50;
		map1['b']=100;
		map1['c']=150;
		map1['d']=200;

		std::cout << "map1 size : " << map1.size() << std::endl;
		std::cout << std::endl << GREY << "Finding and erasing 'b' in map1... " << RESET << std::endl;
		it = map1.find('b');
		if (it != map1.end())
		map1.erase (it);
		std::cout << "map1 size after erasing 'b' : " << map1.size() << std::endl;

		// print content:
		std::cout << "elements in map1:" << '\n';
		std::cout << "a => " << map1.find('a')->second << std::endl;
		std::cout << "c => " << map1.find('c')->second << std::endl;
		std::cout << "d => " << map1.find('d')->second << std::endl;
	}
	std::cout << std::endl << BOLDCYAN << "Count test" << RESET << std::endl;
	{
		std::map<char,int> map1;
		char c;

		map1['a'] = 101;
		map1['c'] = 202;
		map1['f'] = 303;

		for (c = 'a'; c < 'h'; c++)
		{
			std::cout << c;
			if (map1.count(c)>0)
				std::cout << " is an element of map1.\n";
			else
				std::cout << " is not an element of map1.\n";
 		}
	}
	std::cout << std::endl << BOLDCYAN << "Lower and Upper bound test" << RESET << std::endl;
	{
		std::map<char, int> map1;
		std::map<char, int>::iterator itlow, itup;

		map1['a'] = 20;
		map1['b'] = 40;
		map1['c'] = 60;
		map1['d'] = 80;
		map1['e'] = 100;

		itlow = map1.lower_bound('b');  // itlow points to b
		itup = map1.upper_bound('d');   // itup points to e (not d!)

		map1.erase(itlow, itup);        // erases [itlow,itup)

		// print content:
		for (std::map<char,int>::iterator it=map1.begin(); it != map1.end(); ++it)
		std::cout << it->first << " => " << it->second << '\n';
	}
	std::cout << std::endl << BOLDCYAN << "Equal range test" << RESET << std::endl;
	{
		std::map<char,int> map1;

		map1['a'] = 10;
		map1['b'] = 20;
		map1['c'] = 30;

		std::pair<std::map<char, int>::iterator, std::map<char, int>::iterator> ret;
		ret = map1.equal_range('b');

		std::cout << "lower bound points to: ";
		std::cout << ret.first->first << " => " << ret.first->second << '\n';

		std::cout << "upper bound points to: ";
		std::cout << ret.second->first << " => " << ret.second->second << '\n';
	}

	std::cout << std::endl << BOLDCYAN << "Map insert 1 000 000 pairs test" << RESET << std::endl;
	std::map<int, int> mymap;
	int i = 0;
	while (i < 1000000)
	{
		std::pair<int, int> pr = std::make_pair<int, int>(i, i);
		mymap.insert(pr);
		i++;
	}
	std::cout << "Inserted !" << std::endl;
	return (0);
}


