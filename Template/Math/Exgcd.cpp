#include <bits/stdc++.h>

long long exgcd(long long a, long long b, long long &x,
                long long &y) {  // 通解 x = x0 + k * b /gcd(a,b) y = y0 - k * a /gcd(a,b)
    if (!b) {
        x = 1, y = 0;
        return a;
    }
    long long x1, y1, d;
    d = exgcd(b, a % b, x1, y1);
    y = x1 - a / b * y;
    x = y1;
    return d;
}

long long INV(long long a, int MOD) {
    long long x, y, d = exgcd(a, MOD, x, y);
    return d == 1 ? (MOD + x % MOD) % MOD : -1;
}
