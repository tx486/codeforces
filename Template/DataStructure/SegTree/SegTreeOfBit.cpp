#include <bits/stdc++.h>

class SegTreeOfBit {  // 区间异或，维护区间异或,与,或
    using ll = long long;

public:
    SegTreeOfBit(int n) {
        this->n = n;
        Xor.resize(n << 2);
        Or.resize(n << 2);
        And.resize(n << 2);
        xorTag.resize(n << 2);
    }
    SegTreeOfBit(std::vector<ll>& a) {
        this->n = a.size() - 1;
        Xor.resize(n << 2);
        Or.resize(n << 2);
        And.resize(n << 2);
        xorTag.resize(n << 2);
        build(1, n, 1, a);
    }
    void range_xor(int l, int r, ll v) {
        range_xor(l, r, v, 1, n, 1);
    }
    ll query_or(int l, int r) {
        return query_or(l, r, 1, n, 1);
    }
    ll query_xor(int l, int r) {
        return query_xor(l, r, 1, n, 1);
    }

private:
    int n;
    std::vector<ll> And, Or, Xor, xorTag;
    void up(int i) {
        Or[i] = Or[i << 1] | Or[i << 1 | 1];
        Xor[i] = Xor[i << 1] ^ Xor[i << 1 | 1];
        And[i] = And[i << 1] & And[i << 1 | 1];
    }
    void build(int l, int r, int i) {
        if (l == r)
            And[i] = Or[i] = Xor[i] = 0;
        else {
            int mid = (l + r) >> 1;
            build(l, mid, i << 1);
            build(mid + 1, r, i << 1 | 1);
            up(i);
        }
    }
    void build(int l, int r, int i, std::vector<ll>& a) {
        if (l == r)
            And[i] = Or[i] = Xor[i] = a[l - 1];
        else {
            int mid = (l + r) >> 1;
            build(l, mid, i << 1, a);
            build(mid + 1, r, i << 1 | 1, a);
            up(i);
        }
        xorTag[i] = 0;
    }
    void down(int l, int r, int i) {
        if (xorTag[i]) {
            int mid = (l + r) >> 1;
            lazy_xor(l, mid, xorTag[i], i << 1);
            lazy_xor(mid + 1, r, xorTag[i], i << 1 | 1);
            xorTag[i] = 0;
        }
    }
    void lazy_xor(int l, int r, ll v, int i) {
        ll _Or = Or[i], _And = And[i];
        Or[i] = ((~v) & _Or) | (v & (~_And));
        And[i] = ((~v) & _And) | (v & (~_Or));
        if ((r - l + 1) % 2)
            Xor[i] ^= v;
        xorTag[i] ^= v;
    }
    void range_xor(int L, int R, ll v, int l, int r, int i) {
        if (L <= l && r <= R)
            lazy_xor(l, r, v, i);
        else {
            down(l, r, i);
            int mid = (l + r) >> 1;
            if (L <= mid)
                range_xor(L, R, v, l, mid, i << 1);
            if (R > mid)
                range_xor(L, R, v, mid + 1, r, i << 1 | 1);
            up(i);
        }
    }
    ll query_or(int L, int R, int l, int r, int i) {
        if (L <= l && r <= R)
            return Or[i];
        else {
            down(l, r, i);
            int mid = (l + r) >> 1;
            ll res = 0;
            if (L <= mid)
                res |= query_or(L, R, l, mid, i << 1);
            if (R > mid)
                res |= query_or(L, R, mid + 1, r, i << 1 | 1);
            return res;
        }
    }
    ll query_xor(int L, int R, int l, int r, int i) {
        if (L <= l && r <= R)
            return Xor[i];
        else {
            down(l, r, i);
            int mid = (l + r) >> 1;
            ll res = 0;
            if (L <= mid)
                res ^= query_xor(L, R, l, mid, i << 1);
            if (R > mid)
                res ^= query_xor(L, R, mid + 1, r, i << 1 | 1);
            return res;
        }
    }
};