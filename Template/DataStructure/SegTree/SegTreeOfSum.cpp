#include <bits/stdc++.h>

template <typename T>
class SegTree {  // 区间更新,加减，维护累加和 初始为0
public:
    SegTree(int n) {
        this->n = n;
        sum.resize(n << 2);
        addTag.resize(n << 2);
        updateVal.resize(n << 2);
        updateTag.resize(n << 2);
        build(1, n, 1);
    }
    void set(int i, T v) {
        update(i, i, v, 1, n, 1);
    }
    void set(int l, int r, T v) {
        if (l > r)
            return;
        update(l, r, v, 1, n, 1);
    }
    void add(int i, T v) {
        add(i, i, v, 1, n, 1);
    }
    void add(int l, int r, T v) {
        if (l > r)
            return;
        add(l, r, v, 1, n, 1);
    }
    T get(int i) {
        return querySum(i, i, 1, n, 1);
    }
    T querySum(int l, int r) {
        if (l > r)
            return 0;
        return querySum(l, r, 1, n, 1);
    }

private:
    int n;
    std::vector<T> sum, updateVal, addTag;
    std::vector<bool> updateTag;
    void up(int i) {
        sum[i] = sum[i << 1] + sum[i << 1 | 1];
    }
    void build(int l, int r, int i) {
        if (l == r)
            sum[i] = 0;
        else {
            int mid = (l + r) >> 1;
            build(l, mid, i << 1);
            build(mid + 1, r, i << 1 | 1);
            up(i);
        }
        updateTag[i] = false;
        updateVal[i] = 0;
        addTag[i] = 0;
    }
    void down(int l, int r, int i) {
        if (updateTag[i]) {
            int mid = (l + r) >> 1;
            lazy_update(l, mid, updateVal[i], i << 1);
            lazy_update(mid + 1, r, updateVal[i], i << 1 | 1);
            updateTag[i] = false;
        }
        if (addTag[i]) {
            int mid = (l + r) >> 1;
            lazy_add(l, mid, addTag[i], i << 1);
            lazy_add(mid + 1, r, addTag[i], i << 1 | 1);
            addTag[i] = 0;
        }
    }
    void lazy_add(int l, int r, T v, int i) {
        sum[i] += v * (r - l + 1);
        addTag[i] += v;
    }
    void lazy_update(int l, int r, T v, int i) {
        sum[i] = v * (r - l + 1);
        updateVal[i] = v;
        updateTag[i] = true;
        addTag[i] = 0;
    }
    void update(int L, int R, T v, int l, int r, int i) {
        if (L <= l && r <= R)
            lazy_update(l, r, v, i);
        else {
            down(l, r, i);
            int mid = (l + r) >> 1;
            if (L <= mid)
                update(L, R, v, l, mid, i << 1);
            if (R > mid)
                update(L, R, v, mid + 1, r, i << 1 | 1);
            up(i);
        }
    }
    void add(int L, int R, T v, int l, int r, int i) {
        if (L <= l && r <= R)
            lazy_add(l, r, v, i);
        else {
            down(l, r, i);
            int mid = (l + r) >> 1;
            if (L <= mid)
                add(L, R, v, l, mid, i << 1);
            if (R > mid)
                add(L, R, v, mid + 1, r, i << 1 | 1);
            up(i);
        }
    }
    T querySum(int L, int R, int l, int r, int i) {
        if (L <= l && r <= R)
            return sum[i];
        else {
            down(l, r, i);
            int mid = (l + r) >> 1;
            T res = 0;
            if (L <= mid)
                res += querySum(L, R, l, mid, i << 1);
            if (R > mid)
                res += querySum(L, R, mid + 1, r, i << 1 | 1);
            return res;
        }
    }
};