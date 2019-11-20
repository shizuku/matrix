#include "matrix.hpp"
#include <iostream>
#include <time.h>

int main() {
	std::vector<int> {};
	std::cout << "initial:\n";
	auto a = la::matrix<3, 3>({ 1,2,3,4,5,6,7,8,9 });
	auto b = la::matrix<3, 3>({ 6,5,7,6,1,3,5,9,4 });
	std::cout << a;
	std::cout << b;

	std::cout << "transposition:\n";
	a = ~a;
	std::cout << a;

	std::cout << "matrix product:\n";
	a %= b;
	std::cout << a;

	std::cout << "negtive:\n";
	a = -a;
	std::cout << a;

	std::cout << "plus\n";
	b += a;
	std::cout << b;

	std::cout << "minus\n";
	b -= a;
	std::cout << b;

	std::cout << "multiply:\n";
	a *= 5;
	std::cout << a;

	std::cout << "divide:\n";
	a /= 10;
	std::cout << a;

	std::cout << "usage of itorator:\n";
	for (auto i = a.cbegin(); i != a.cend(); ++i) {
		std::cout << *i << "\t";
	}
	std::cout << "\n";
	for (auto i = a.crbegin(); i != a.crend(); --i) {
		std::cout << *i << "\t";
	}
	std::cout << "\n";
	for (auto i = a.begin(); i != a.end(); ++i) {
		*i =1;
	}
	std::cout << a;

	//system("pause");
	return 0;
}
