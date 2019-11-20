# matrix
[English](./README.md)

所有的类和方法都包含在la（Linear Algebra的缩写）名称空间中。

一个计算矩阵的c++模板类.

只在Visual Studio上编译通过

## 用法
```c++
auto a = la::matrix<3, 3>({ 1,2,3,4,5,6,7,8,9 });
auto b = la::matrix<3, 3>({ 6,5,7,6,1,3,5,9,4 });
//用 vector初始化两个矩阵
```
```c++
std::cout << a; //输出到控制台
```
```c++
print(hdc, a); //输出到 Windows窗体
//以灰度形式绘图
```
```c++
a = -a; //取负
```
```c++
a = ~a; //转置
```
```c++
b += a; //加法
auto c = b + a; //加法
```
```c++
b -= a;
auto c = b - a;
```
```c++
a *= 5;
auto c = a * 5; //5*a 同样合法并且等价
//如果要计算两个矩阵的程序，请使用运算符 %
```
```c++
a /= 10;
auto c = a/10; // 10/a 是非法的
```
```c++
auto c = a % b; //计算矩阵乘积
a %= b; //只有当 a和 b都是方阵时才能使用
```
```c++
//迭代器的用法与 std::vector相似
for (auto iter = a.begin(); iter != a.end(); ++iter) {
    std::cout << *i << "\t";
}
//const_iterator（const迭代器）， reverse_iterator（反向迭代器）, const_reverse_iterator（const反向带迭器） 同样可用
//注意必须对反向迭代器使用 --iter
```
