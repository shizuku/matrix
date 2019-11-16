# matrix
A cpp template class to calculate matrix.  
一个计算矩阵的c++模板类.


```c++
//1. one thread
//time cost(Debug): more than 1min
//time cost(Rlease): 37.355s
for (int i = 1; i <= _A; i++) {
    for (int j = 1; j <= _C; j++) {
        for (int k = 1; k <= _B; k++) {
            s->at(i, j) += a.at(i, k) * b.at(k, j);
        }
    }
}

//2. multithread, only work in Visual Studio
//time cost(Debug): more than 1min
//time cost(Release): 37.099s
auto q = [&](int x,int y) {
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
}
```