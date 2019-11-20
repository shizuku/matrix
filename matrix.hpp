#pragma once
#include <vector>
#include <iostream>
#include <string>
#include <thread>
#include <Windows.h>

const int cores = 8;

namespace la {
template<size_t _M, size_t _N, typename _T = double>
class matrix {
public:
	//using difference_type = typename matrix::difference_type;
	matrix() {
		head = new _T[_M * _N]();
		tail = head + _M * _N;
		fill();
	}
	matrix(std::vector<_T>& a) {
		head = new _T[_M * _N]();
		tail = head + _M * _N;
		fill(a);
	}
	matrix(const matrix<_M, _N, _T>& src) {
		head = new _T[_M * _N]();
		tail = head + _M * _N;
		auto j = this->begin();
		for (auto i = src.cbegin(); i != src.cend(); ++i,++j) {
			*j = *i;
		}
	}
	matrix(const matrix<_M, _N, _T>&& src) noexcept{
		head = new _T[_M * _N]();
		tail = head + _M * _N;
		auto j = this->begin();
		for (auto i = src.cbegin(); i != src.cend(); ++i,++j) {
			*j = *i;
		}
	}
	matrix<_M, _N, _T>& operator=(const matrix<_M, _N, _T>& src){
		if (this == &src) {
			return *this;
		}
		for (int i = 0; i < _M; i++) {
			for (int j = 0; j < _N; j++) {
				fat(i, j) = src.fcat(i,j);
			}
		}
		return *this;
	}
	~matrix() { delete [] head; }

	class const_iterator {
	public:
		const_iterator(_T* i) : item(i) {}

		const _T& operator*() const {
			return *item;
		}
		const _T* operator->() const {
			return item;
		}
		const _T& operator[](const size_t _Off) const {
			return *(item + _Off);
		}

		const_iterator& operator++() {
			++item;
			return *this;
		}
		const_iterator operator++(int) {
			const_iterator _Tmp = *this;
			const_iterator::operator++();
			return _Tmp;
		}
		const_iterator& operator--() {
			--item;
			return *this;
		}
		const_iterator operator--(int) {
			const_iterator _Tmp = *this;
			const_iterator::operator--();
			return _Tmp;
		}
		const_iterator& operator+=(const int i) {
			item += i;
			return *this;
		}
		const_iterator operator+(const int i) const {
			const_iterator _Tmp = *this;
			return _Tmp += i;
		}
		const_iterator& operator-=(const int i) {
			item -= i;
			return *this;
		}
		const_iterator operator-(const int _Off) const {
			const_iterator _Tmp = *this;
			return _Tmp -= _Off;
		}

		bool operator==(const const_iterator& _Right) const {
			return item == _Right.item;
		}
		bool operator!=(const const_iterator& _Right) const {
			return !(*this == _Right);
		}
		bool operator<(const const_iterator& _Right) const {

			return item < _Right.item;
		}
		bool operator>(const const_iterator& _Right) const {
			return _Right < *this;
		}
		bool operator<=(const const_iterator& _Right) const {
			return !(_Right < *this);
		}
		bool operator>=(const const_iterator& _Right) const {
			return !(*this < _Right);
		}

	private:
		_T* item;
	};
	class iterator {
	public:
		iterator(_T* i) : item(i) {}

		_T& operator*() {
			return *item;
		}
		/*const _T& operator*() const {
			return *item;
		}*/
		_T* operator->() {
			return item;
		}
		/*const _T* operator->() const {
			return item;
		}*/
		_T& operator[](const size_t _Off) {
			return *(item + _Off);
		}
		/*const _T& operator[](const size_t _Off) const {
			return *(item + _Off);
		}*/

		iterator& operator++(){
			++item;
			return *this;
		}
		iterator operator++(int) {
			iterator _Tmp = *this;
			iterator::operator++();
			return _Tmp;
		}
		iterator& operator--() {
			--item;
			return *this;
		}
		iterator operator--(int) {
			iterator _Tmp = *this;
			iterator::operator--();
			return _Tmp;
		}
		iterator& operator+=(const int i){
			item += i;
			return *this;
		}
		iterator operator+(const int i) const {
			iterator _Tmp = *this;
			return _Tmp += i;
		}
		iterator& operator-=(const int i) {
			item -= i;
			return *this;
		}
		iterator operator-(const int _Off) const {
			iterator _Tmp = *this;
			return _Tmp -= _Off;
		}

		bool operator==(const iterator& _Right) const {
			return item == _Right.item;
		}
		bool operator!=(const iterator& _Right) const {
			return !(*this == _Right);
		}
		bool operator<(const iterator& _Right) const {

			return item < _Right.item;
		}
		bool operator>(const iterator& _Right) const {
			return _Right < *this;
		}
		bool operator<=(const iterator& _Right) const {
			return !(_Right < *this);
		}
		bool operator>=(const iterator& _Right) const {
			return !(*this < _Right);
		}

	private:
		_T* item;
	};

	void fill() {
		for (int i = 0; i < _M; i++) {
			for (int j = 0; j < _N; j++) {
				at(i, j) = 0;
			}
		}
	}
	void fill(std::vector<_T>& a) {
		int size = a.size();
		int k = 0;
		for (int i = 0; i < _M; i++) {
			for (int j = 0; j < _N; j++) {
				if (k < size) {
					fat(i, j) = a[k];
					k++;
				}
				else {
					fat(i, j) = 0;
					k++;
				}
			}
		}
	}

	_T& at(size_t m, size_t n) {
		_T* r = (head + (m * _N + n));
		if (r < tail && r >= head) {
			return *r;
		}
		else {
			throw std::out_of_range("matrix out of range");
		}
	}
	_T& fat(size_t m, size_t n) {
		return *(head + (m * _N + n));
	}
	const _T& cat(size_t m, size_t n) const {
		_T* r = (head + (m * _N + n));
		if (r < tail && r >= head) {
			return *r;
		}
		else {
			throw std::out_of_range("matrix out of range");
		}
	}
	const _T& fcat(size_t m, size_t n) const {
		return *(head + (m * _N + n));
	}
	
	_T sum() {
		_T r = _T();
		for (int i = 0; i < _M; ++i) {
			for (int j = 0; j < _N; ++j) {
				r += fat(i, j);
			}
		}
		return r;
	}
	inline const matrix<_N, _M, _T> transposition() const {
		return ~*this;
	}

	void save_as(std::string filename) {
		std::ofstream of(filename);
		for (int i = 0; i < _M; ++i) {
			for (int j = 0; j < _N; ++j) {
				of << fat(i, j) << " ";
			}
		}
	}
	void read_from(std::string filename) {
		std::ifstream of(filename);
		for (int i = 0; i < _M; ++i) {
			for (int j = 0; j < _N; ++j) {
				of >> fat(i, j);
			}
		}
	}

	const matrix<_M, _N, _T> operator+() const {
		return *this;
	}
	const matrix<_M, _N, _T> operator-() const {
		matrix<_M, _N, _T> tmp(*this);
		for (auto i = tmp.begin(); i != tmp.end(); ++i) {
			*i = -*i;
		}
		return tmp;
	}
	const matrix<_N, _M, _T> operator~() const {
		matrix<_N, _M, _T> s = matrix<_N, _M, _T>();
		for (int i = 0; i < _N; i++) {
			for (int j = 0; j < _M; j++) {
				s.fat(i, j) = this->fcat(j, i);
			}
		}
		return s;
	}
	matrix<_M, _N, _T>& operator+=(const matrix<_M, _N, _T> src) {
		return *this = *this + src;
	}
	matrix<_M, _N, _T>& operator-=(const matrix<_M, _N, _T> src) {
		return *this = *this - src;
	}
	template<class _TTy>
	matrix<_M, _N, _T>& operator*=(const _TTy src) {
		return *this = *this * _T(src);
	}
	template<class _TTy>
	matrix<_M, _N, _T>& operator/=(const _TTy src) {
		return *this = *this / _T(src);
	}
	template<size_t _A, typename _T>
	matrix<_A, _A, _T>& operator%=(const matrix<_A, _A, _T> src) {
		return *this = *this % src;
	}

	matrix::iterator begin() { return iterator(head); }
	matrix::iterator end() { return iterator(tail); }
	matrix::iterator rbegin() { return iterator(tail-1); }
	matrix::iterator rend() { return iterator(head-1); }
	const matrix::const_iterator cbegin() const { return const_iterator(head); }
	const matrix::const_iterator cend() const { return const_iterator(tail); }
	const matrix::const_iterator crbegin() const { return const_iterator(tail - 1); }
	const matrix::const_iterator crend() const { return const_iterator(head - 1); }

private:
	_T* head;
	_T* tail;
};

template<size_t _A, size_t _B, typename _Ty>
la::matrix<_A, _B, _Ty> operator+(const la::matrix<_A, _B, _Ty>& a, const la::matrix<_A, _B, _Ty>& b) {
	la::matrix<_A, _B, _Ty> s =  la::matrix<_A, _B, _Ty>();
	for (int i = 0; i < _A; i++) {
		for (int j = 0; j < _B; j++) {
			s.fat(i, j) = a.fcat(i, j) + b.fcat(i, j);
		}
	}
	return s;
}

template<size_t _A, size_t _B, typename _Ty>
la::matrix<_A, _B, _Ty> operator-(const la::matrix<_A, _B, _Ty>& a, const la::matrix<_A, _B, _Ty>& b) {
	la::matrix<_A, _B, _Ty> s = la::matrix<_A, _B, _Ty>();
	for (int i = 0; i < _A; i++) {
		for (int j = 0; j < _B; j++) {
			s.fat(i, j) = a.fcat(i, j) - b.fcat(i, j);
		}
	}
	return s;
}

template<size_t _A, size_t _B, typename _Ty, typename _T>
la::matrix<_A, _B, _Ty> operator*(const la::matrix<_A, _B, _Ty>& a, const _T& b) {
	la::matrix<_A, _B, _Ty> s = la::matrix<_A, _B, _Ty>();
	for (int i = 0; i < _A; i++) {
		for (int j = 0; j < _B; j++) {
			s.fat(i, j) = a.fcat(i, j) * _Ty(b);
		}
	}
	return s;
}
template<size_t _A, size_t _B, typename _Ty, typename _T>
inline la::matrix<_A, _B, _Ty> operator*(const _T& b, const la::matrix<_A, _B, _Ty>& a) {
	return operator*(a,b);
}

template<size_t _A, size_t _B, typename _Ty, typename _T>
la::matrix<_A, _B, _Ty> operator/(const la::matrix<_A, _B, _Ty>& a, const _T& b) {
	la::matrix<_A, _B, _Ty> s = la::matrix<_A, _B, _Ty>();
	for (int i = 0; i < _A; i++) {
		for (int j = 0; j < _B; j++) {
			s.fat(i, j) = a.fcat(i, j) / _Ty(b);
		}
	}
	return s;
}

template<size_t _A, size_t _B, size_t _C, typename _Ty>
la::matrix<_A, _C, _Ty> operator%(const la::matrix<_A, _B, _Ty>& a, const la::matrix<_B, _C, _Ty>& b) {
	la::matrix<_A, _C, _Ty> s = la::matrix<_A, _C, _Ty>();

	if (_A < cores) {
		for (int i = 0; i < _A; i++) {
			for (int j = 0; j < _C; j++) {
				for (int k = 0; k < _B; k++) {
					s.at(i, j) += a.cat(i, k) * b.cat(k, j);
				}
			}
		}
	}
	else {
		auto q = [&](int x, int y) {
			for (int i = x; i < y; i++) {
				for (int j = 0; j < _C; j++) {
					for (int k = 0; k < _B; k++) {
						s.fat(i, j) += a.fcat(i, k) * b.fcat(k, j);
					}
				}
			}
		};
		std::vector<int> it = std::vector<int>(cores * 2);
		std::vector<std::thread> pool = std::vector<std::thread>();
		it[0] = 0;
		it[1] = _A / cores;
		for (int i = 2; i < cores * 2 - 2; i += 2) {
			it[i] = it[i - 1];
			it[i + 1] = it[i - 1] + _A / cores;
		}
		it[cores * 2 - 2] = it[cores * 2 - 3];
		it[cores * 2 - 1] = _A;
		for (int i = 0; i < cores; i++) {
			pool.push_back(std::thread(q, it[i * 2], it[i * 2 + 1]));
		}
		for (auto i = pool.begin(); i != pool.end(); ++i) {
			i->join();
		}
	}
	return s;
}

template<size_t _A, size_t _B, typename _Ty>
std::ostream& print(std::ostream& ostr, const la::matrix<_A, _B, _Ty>& a, int b) {
	int p1 = 0, p2 = 0, p3 = 0, p4 = 0;
	std::string x = "", y = "";
	if (b && _B > 10) {
		p1 = 5, p2 = _B - 5;
		x = "...\t";
	}
	else {
		p1 = _B / 2;
		p2 = p1;
	}
	if (b && _A > 10) {
		p3 = 5, p4 = _A - 5;
		y = " ...\n";
	}
	else {
		p3 = _A / 2;
		p4 = p3;
	}
	char h = '[';
	for (int i = 0; i < p3; i++) {
		ostr << h;
		if (i == 0) h = ' ';
		ostr << "[\t";
		for (int j = 0; j < p1; j++) {
			ostr << a.fcat(i, j) << "\t";
		}
		ostr << x;
		for (int j = p2; j < _B; j++) {
			ostr << a.fcat(i, j);
			if (j != _B-1)
				ostr << "\t";
		}
		ostr << "\t]\n";
	}
	ostr << y;
	for (int i = p4; i < _A; i++) {
		ostr << h << "[\t";
		for (int j = 0; j < p1; j++) {
			ostr << a.fcat(i, j) << "\t";
		}
		ostr << x;
		for (int j = p2; j < _B; j++) {
			ostr << a.fcat(i, j);
			if (j != _B-1)
				ostr << "\t";
		}
		ostr << "\t]";
		if (i != _A-1)ostr << "\n";
	}
	ostr << "] " << _A << "*" << _B << "\n";
	return ostr;
}

template<size_t _A, size_t _B, typename _Ty>
std::ostream& operator<<(std::ostream& ostr, const la::matrix<_A, _B, _Ty>& a) { return print(ostr, a, 1); }

const int wdt = 10;
template<size_t _A, size_t _B, typename _Ty>
int print(HDC hdc, const la::matrix<_A, _B, _Ty>& a) {
	for (int i = 1; i <= _A; i++) {
		for (int j = 1; j <= _B; j++) {
			SelectObject(hdc, CreateSolidBrush(RGB(255 - a.fcat(i, j), 255 - a.fcat(i, j), 255 - a.fcat(i, j))));
			Rectangle(hdc, j * wdt, i * wdt, (j + 1) * wdt - 1, (i + 1) * wdt - 1);
		}
	}
	return 0;
}

template<size_t _A, size_t _B, typename _Ty>
const la::matrix<_A, _B, _Ty> transposition(const la::matrix<_B, _A, _Ty>& x) {
	return ~x;
}

};
