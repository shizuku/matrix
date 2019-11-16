
#include <thread>
#include "matrix.hpp"
#include <iostream>
#include <time.h>


int main()
{
	const size_t si = 500;
    const size_t sj = 500;
    

	std::vector<double>* t = new std::vector<double>(si * sj, 5);
	la::matrix<si, sj>* b = new la::matrix<si, sj>(t);
	la::matrix<sj, si>* c = new la::matrix<sj, si>(t);

	//std::cout << *b;
	//std::cout << *c;
	time_t x1 = clock();
	auto a = dot(b, c);
	time_t y1 = clock();

	std::cout << *a;

	std::cout << "" << (y1 - x1) / double(CLOCKS_PER_SEC) << "(s)\n";
	
	//system("pause");
	return 0;
}
