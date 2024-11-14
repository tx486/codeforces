#include <bits/stdc++.h>

static constexpr int MOD = 1e9 + 7;

std::vector<long long> fac;
long long fp(long long a, long long b) {
    long long res = 1;
    while (b) {
        if (b & 1)
            res = res * a % MOD;
        b >>= 1;
        a = a * a % MOD;
    }
    return res;
}
long long inv(long long a) {
    return fp(a, MOD - 2);
}
long long comb(int a, int b) {
    return fac[a] * inv(fac[b]) % MOD * inv(fac[a - b]) % MOD;
}
long long perm(int a, int b) {
    return fac[a] * inv(fac[a - b]) % MOD;
}
void init(int n) {
    fac.resize(n + 1);
    fac[0] = 1;
    for (int i = 1; i <= n; i++) {
        fac[i] = fac[i - 1] * i % MOD;
    }
}