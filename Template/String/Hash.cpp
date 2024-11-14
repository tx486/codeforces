#include <bits/stdc++.h>
using namespace std;

class SingleHash {
    using ull = unsigned long long;

private:
    vector<ull> pw, pre;
    static int BASE;

public:
    SingleHash(string& s) {
        int n = s.size();
        pw.resize(n + 1);
        pre.resize(n + 1);
        pw[0] = 1;
        for (int i = 1; i <= n; i++) {
            pw[i] = pw[i - 1] * BASE;
            pre[i] = pre[i - 1] * BASE + s[i - 1];
        }
    }
    ull hash(int l, int r) {
        return pre[r + 1] - pre[l] * pw[r - l + 1];
    }
};
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
int SingleHash::BASE = uniform_int_distribution<>(8e8, 9e8)(rng);

class DoubleHash {
    using u32 = unsigned int;

private:
    vector<u32> pw1, pre1, pw2, pre2;
    static int BASE1, BASE2;

public:
    DoubleHash(string& s) {
        int n = s.size();
        pw1.resize(n + 1);
        pre1.resize(n + 1);
        pw1[0] = 1;
        pw2.resize(n + 1);
        pre2.resize(n + 1);
        pw2[0] = 1;
        for (int i = 1; i <= n; i++) {
            pw1[i] = pw1[i - 1] * BASE1;
            pre1[i] = pre1[i - 1] * BASE1 + s[i - 1];
            pw2[i] = pw2[i - 1] * BASE2;
            pre2[i] = pre2[i - 1] * BASE2 + s[i - 1];
        }
    }
    unsigned long long hash(int l, int r) {
        u32 h1 = pre1[r + 1] - pre1[l] * pw1[r - l + 1];
        u32 h2 = pre2[r + 1] - pre2[l] * pw2[r - l + 1];
        return (unsigned long long)h1 << 32 | h2;
    }
};
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
int DoubleHash::BASE1 = 233 + uniform_int_distribution<>(8e8, 9e8)(rng);
int DoubleHash::BASE2 = 499 + uniform_int_distribution<>(8e8, 9e8)(rng);
