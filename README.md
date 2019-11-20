# matrix
[中文](./README_zh_CN.md)

All class and methods is included in namespace la (the acronym of Linear Algebra).

A cpp template class to calculate matrix.  

Only work well in Visual Studio.

## Usage
```c++
auto a = la::matrix<3, 3>({ 1,2,3,4,5,6,7,8,9 });
auto b = la::matrix<3, 3>({ 6,5,7,6,1,3,5,9,4 });
//init two matrix using vector
```
```c++
std::cout << a; //out put matrix to consale
```
```c++
print(hdc, a); //out put matrix to Windows framework
//paint in gray degree
```
```c++
a = -a; //negative
```
```c++
a = ~a; //transposition
```
```c++
b += a; //add a to b
auto c = b + a; //calculate sum of two matrix
```
```c++
b -= a;
auto c = b - a;
```
```c++
a *= 5;
auto c = a * 5; //5*a is also legal and equal
//if you want to calculate product of two matrix, olease use operator%
```
```c++
a /= 10;
auto c = a/10; // 10/a is illegal
```
```c++
auto c = a % b; //calculate product of two matrix
a %= b; //only available when both a & b is square matrix
```
```c++
//usage of iterator is similar to std::vector
for (auto iter = a.begin(); iter != a.end(); ++iter) {
    std::cout << *i << "\t";
}
//there are const_iterator, reverse_iterator, const_reverse_iterator available
//pay attention to use --iter when using reverse_iterator
```
