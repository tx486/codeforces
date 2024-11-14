#include <bits/stdc++.h>
using namespace std;

template <typename T>
struct Fenwick {
public:
    Fenwick() {
    }
    Fenwick(int n) {
        this->n = n;
        tr.assign(n + 1, 0);
    }
    void add(int i, T x) {
        for (; i <= n; i += i & -i) tr[i] += x;
    }
    T sum(int i) {
        T ret = 0;
        for (; i; i -= i & -i) ret += tr[i];
        return ret;
    }
    T range(int l, int r) {
        if (r < l)
            return 0;
        return sum(r) - sum(l - 1);
    }

private:
    int n;
    vector<T> tr;
};