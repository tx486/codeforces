#include <bits/stdc++.h>

static const int MOD = 1e9 + 7;
std::vector<std::vector<long long>> Stirling(int n, int m) {  // 将N个有标号的物品划分为M个无标号非空集合的方案数
    std::vector<std::vector<long long>> S(n + 1, std::vector<long long>(m + 1));
    S[0][0] = 1;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            S[i][j] = S[i - 1][j - 1] + S[i - 1][j] * j;
            S[i][j] %= MOD;
        }
    }
    return S;
}