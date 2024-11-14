#include <bits/stdc++.h>

constexpr int MOD = 1e9 + 7;

template <typename T>
std::vector<std::vector<T>> mul(std::vector<std::vector<T>> A, std::vector<std::vector<T>> B) {
    int n = A.size(), m = B[0].size();
    std::vector<std::vector<T>> C(n, std::vector<T>(m));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            for (int k = 0; k < B.size(); k++) {
                C[i][j] += A[i][k] * B[k][j] % MOD;
                C[i][j] %= MOD;
            }
        }
    }
    return C;
}

template <typename T>
std::vector<std::vector<T>> fp(std::vector<std::vector<T>> A, T b) {
    int n = A.size();
    std::vector<std::vector<T>> C(n, std::vector<T>(n));
    for (int i = 0; i < n; i++) C[i][i] = 1;
    while (b) {
        if (b & 1)
            C = mul(C, A);
        A = mul(A, A);
        b >>= 1;
    }
    return C;
}