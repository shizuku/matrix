#pragma once
#include <thread>
#include <vector>
#include <iostream>
#include <string>


const int cores = 4;
namespace la {
template<size_t _M, size_t _N, typename _T = double>
class matrix {
public:
	matrix() { fill(nullptr); }
	matrix(std::vector<_T>& a) { fill(a); }
	matrix(std::vector<_T>* a) { fill(a); }
	void fill(std::vector<_T>& a) {
		int size = a.size();
		int k = 0;
		for (int i = 0; i < _M; i++) {
			for (int j = 0; j < _N; j++) {
				if (k < size) {
					s[i][j] = a[k];
					k++;
				}
				else {
					s[i][j] = 0;
					k++;
				}
			}
		}
	}
	void fill(std::vector<_T>* q) {
		std::vector<_T>* a = nullptr;
		int size = 0;
		if (q == nullptr) {
			size = 0;
		}
		else {
			a = q; size = a->size();
		}
		int k = 0;
		for (int i = 0; i < _M; i++) {
			for (int j = 0; j < _N; j++) {
				if (k < size) {
					s[i][j] = (*a)[k];
					k++;
				}
				else {
					s[i][j] = 0;
					k++;
				}
			}
		}
	}
	_T& at(size_t m, size_t n) {
		return s[m - 1][n - 1];
	}
private:
	_T s[_M][_N];
};
};
template<size_t _A, size_t _B, typename _Ty>
std::ostream& operator<<(std::ostream& ostr, la::matrix<_A, _B,_Ty>& a) {
	int p1 = 0, p2 = 0, p3 = 0, p4 = 0;
	std::string x = "", y = "";
	if (_B >= 10) {
		p1 = 5, p2 = _B-5;
		x = "...\t";
	}
	else {
		p1 = _B / 2;
		p2 = p1 + 1;
	}
	if (_A >= 10) {
		p3 = 5, p4 = _A-5;
		y = "...\n";
	}
	else {
		p3 = _A / 2;
		p4 = p3 + 1;
	}
	char h = '[';
	for (int i = 1; i <= p3; i++) {
		ostr << h;
		if (i == 1) h = ' ';
		ostr << "[";
		for (int j = 1; j <= p1; j++) {
			ostr << a.at(i, j) << "\t";
		}
		ostr << x;
		for (int j = p2; j <= _B; j++) {
			ostr << a.at(i, j);
			if(j!= _B)
			ostr << "\t";
		}
		ostr << "]\n";
	}
	ostr << h << y;
	for (int i = p4; i <= _A; i++) {
		ostr << h << "[";
		for (int j = 1; j <= p1; j++) {
			ostr << a.at(i, j) << "\t";
		}
		ostr << x;
		for (int j = p2; j <= _B; j++) {
			ostr << a.at(i, j);
			if (j != _B)
			ostr << "\t";
		}
		ostr << "]";
		if(i!=_A)ostr << "\n";
	}
	ostr << "] " << _A << "*" << _B << "\n";
	return ostr;
}

template<size_t _A, size_t _B,typename _Ty>
la::matrix<_A, _B,_Ty> operator+(la::matrix<_A, _B, _Ty>& a, la::matrix<_A, _B,_Ty>& b) {
	la::matrix<_A, _B> s;
	for (int i = 1; i <= _A; i++) {
		for (int j = 1; j <= _B; j++) {
			s.at(i,j) = a.at(i,j) + b.at(i,j);
		}
	}
	return s;
}
template<size_t _A, size_t _B,typename _Ty>
la::matrix<_A, _B,_Ty> operator-(la::matrix<_A, _B,_Ty>& a, la::matrix<_A, _B,_Ty>& b) {
	la::matrix<_A, _B> s;
	for (int i = 1; i <= _A; i++) {
		for (int j = 1; j <= _B; j++) {
			s.at(i,j) = a.at(i,j) - b.at(i,j);
		}
	}
	return s;
}

template<size_t _A, size_t _B, size_t _C, typename _Ty>
la::matrix<_A, _C, _Ty>* dot(la::matrix<_A, _B, _Ty>& a, la::matrix<_B, _C, _Ty>& b) {
	la::matrix<_A, _C, _Ty>* s = new la::matrix<_A, _C, _Ty>();
	
	for (int i = 1; i <= _A; i++) {
		for (int j = 1; j <= _C; j++) {
			for (int k = 1; k <= _B; k++) {
				s->at(i, j) += a.at(i, k) * b.at(k, j);
			}
		}
	}

	/*auto q = [&](int x,int y) {
		for (int i = x; i <= y; i++) {
			for (int j = 1; j <= _C; j++) {
				for (int k = 1; k <= _B; k++) {
					s->at(i, j) += a.at(i, k) * b.at(k, j);
				}
			}
		}
	};
	std::vector<int> it = std::vector<int>(cores*2);
	std::vector<std::thread> pool;
	it[0] = 1;
	it[1] = _A/cores;
	for (int i = 2; i < cores*2-2; i+=2) {
		it[i] = it[i - 1] + 1;
		it[i + 1] = it[i - 1] + _A / cores;
	}
	it[cores * 2 - 2] = it[cores * 2 - 3] + 1;
	it[cores * 2 - 1] = _A;
	for (int i = 0; i < cores; i++) {
		pool.push_back(std::thread(q, it[i * 2], it[i * 2 + 1]));
	}
	for (auto i = pool.begin(); i != pool.end(); ++i) {
		i->join();
	}*/
	
	return s;
}
template<size_t _A, size_t _B, size_t _C, typename _Ty>
inline la::matrix<_A, _C, _Ty>* dot(la::matrix<_A, _B, _Ty>*& a, la::matrix<_B, _C, _Ty>*& b) { return dot(*a, *b); }
