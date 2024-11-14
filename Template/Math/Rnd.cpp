#include <bits/stdc++.h>

template <typename T>
T rnd(T a, T b) {
    std::mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
    return std::uniform_real_distribution<>(a, b)(rng);
}