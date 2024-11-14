#include <bits/stdc++.h>

int BIT, MX;

unsigned long long pw[17][62];
int len[17];

auto init = [] {
    for (int i = 2; i <= 16; i++) {
        pw[i][0] = 1;
        for (int j = 1; j <= 62; j++) {
            pw[i][j] = pw[i][j - 1] * i;
            if (pw[i][j] > 1e18 || pw[i][j] < 0) {
                len[i] = j;
                break;
            }
        }
    }
    return 0;
}();

int get(long long u, int i) {
    return u / pw[BIT][i] % BIT;
}

int bitLen(long long x) {
    for (int i = len[BIT]; i >= 0; i--)
        if (get(x, i) > 0)
            return i + 1;
    return 0;
}

auto sum = [](long long x) -> long long {  // 1-x 在BIT进制下的所有数位和
    MX = BIT - 1;
    long long res = 0;
    int power = bitLen(x) - 1;
    long long suf = 0, pre = x, full = 0;
    for (int i = 0; i <= power; i++) {
        pre /= BIT;
        int v = get(x, i);
        res += 1ll * v * (pre * pw[BIT][i] + suf + 1);
        res += 1ll * v * (v - 1) / 2 * (pre * pw[BIT][i] + full + 1);
        if (pre)
            res += 1ll * (v + 1 + MX) * (MX - v) / 2 * ((pre - 1) * pw[BIT][i] + full + 1);
        suf += v * pw[BIT][i];
        full += MX * pw[BIT][i];
    }
    return res;
};