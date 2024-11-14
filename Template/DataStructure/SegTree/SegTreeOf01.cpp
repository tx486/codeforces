#include <bits/stdc++.h>

class SegTree {  // 01线段树 维护区间01数量 支持区间反转 初始为0
public:
    SegTree() {
    }
    SegTree(int n) : n(n) {
        cnt0.resize(n << 2);
        cnt1.resize(n << 2);
        reverseTag.resize(n << 2);
        build(1, n, 1);
    }
    void resize(int n) {
        this->n = n;
        cnt0.resize(n << 2);
        cnt1.resize(n << 2);
        reverseTag.resize(n << 2);
        build(1, n, 1);
    }
    void reverse(int i) {
        reverse(i, i, 1, n, 1);
    }
    void reverse(int l, int r) {
        reverse(l, r, 1, n, 1);
    }
    int query_one(int l, int r) {
        return query_one(l, r, 1, n, 1);
    }
    int query_zero(int l, int r) {
        return query_zero(l, r, 1, n, 1);
    }

private:
    int n;
    std::vector<int> cnt0, cnt1;
    std::vector<bool> reverseTag;
    void up(int i) {
        cnt0[i] = cnt0[i << 1] + cnt0[i << 1 | 1];
        cnt1[i] = cnt1[i << 1] + cnt1[i << 1 | 1];
    }
    void build(int l, int r, int i) {
        if (l == r)
            cnt0[i] = 1, cnt1[i] = 0;
        else {
            int mid = (l + r) >> 1;
            build(l, mid, i << 1);
            build(mid + 1, r, i << 1 | 1);
            up(i);
        }
    }
    void down(int l, int r, int i) {
        if (reverseTag[i]) {
            int mid = (l + r) >> 1;
            lazy_reverse(l, mid, i << 1);
            lazy_reverse(mid + 1, r, i << 1 | 1);
            reverseTag[i] = !reverseTag[i];
        }
    }
    void lazy_reverse(int l, int r, int i) {
        std::swap(cnt0[i], cnt1[i]);
        reverseTag[i] = !reverseTag[i];
    }
    void reverse(int L, int R, int l, int r, int i) {
        if (L <= l && r <= R)
            lazy_reverse(l, r, i);
        else {
            down(l, r, i);
            int mid = (l + r) >> 1;
            if (L <= mid)
                reverse(L, R, l, mid, i << 1);
            if (R > mid)
                reverse(L, R, mid + 1, r, i << 1 | 1);
            up(i);
        }
    }
    int query_one(int L, int R, int l, int r, int i) {
        if (L <= l && r <= R)
            return cnt1[i];
        else {
            down(l, r, i);
            int mid = (l + r) >> 1;
            int res = 0;
            if (L <= mid)
                res += query_one(L, R, l, mid, i << 1);
            if (R > mid)
                res += query_one(L, R, mid + 1, r, i << 1 | 1);
            return res;
        }
    }
    int query_zero(int L, int R, int l, int r, int i) {
        if (L <= l && r <= R)
            return cnt0[i];
        else {
            down(l, r, i);
            int mid = (l + r) >> 1;
            int res = 0;
            if (L <= mid)
                res += query_zero(L, R, l, mid, i << 1);
            if (R > mid)
                res += query_zero(L, R, mid + 1, r, i << 1 | 1);
            return res;
        }
    }
};

template <typename T>
class BitQuery {
private:
    int BIT, n;
    std::vector<SegTree> tr;

public:
    BitQuery(int n, int BIT) : n(n), BIT(BIT) {
    }
    void init(std::vector<T>& a) {
        tr.assign(BIT, SegTree(n));
        for (int i = 1; i <= n; i++)
            for (int j = 0; j < BIT; j++)
                if (a[i - 1] >> j & 1)
                    tr[j].reverse(i);
    }
    void range_xor(int l, int r, T v) {
        for (int i = 0; i < BIT; i++) {
            if (v >> i & 1) {
                tr[i].reverse(l, r);
            }
        }
    }
    T query_xor(int l, int r) {
        T ans = 0;
        for (int i = 0; i < BIT; i++) {
            if (tr[i].query_one(l, r) % 2) {
                ans |= 1 << i;
            }
        }
        return ans;
    }
    T query_or(int l, int r) {
        T ans = 0;
        for (int i = 0; i < BIT; i++) {
            if (tr[i].query_one(l, r)) {
                ans |= 1 << i;
            }
        }
        return ans;
    }
    T query_and(int l, int r) {
        T ans = 0;
        for (int i = 0; i < BIT; i++) {
            if (!tr[i].query_zero(l, r)) {
                ans |= 1 << i;
            }
        }
        return ans;
    }
};