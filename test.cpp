#include "matrix.hpp"
#include <iostream>
#include <time.h>
int main()
{
	const size_t si = 10000;
    const size_t sj = 1;
    
	time_t x0 = clock();
	std::vector<double>* t = new std::vector<double>(si * si, 5);
	la::matrix<si, sj>* b = new la::matrix<si, sj>(t);
	la::matrix<sj, si>* c = new la::matrix<sj, si>(t);
	time_t y0 = clock();

	time_t x1 = clock();
	auto a = dot(b, c);
	time_t y1 = clock();

	std::cout << *a;
	std::cout << "" << (y0 - x0) / double(CLOCKS_PER_SEC) << "(s)\n";
	std::cout << "" << (y1 - x1) / double(CLOCKS_PER_SEC) << "(s)\n";
	
	system("pause");
	return 0;
}
