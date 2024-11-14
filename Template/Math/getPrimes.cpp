#include <bits/stdc++.h>

std::vector<int> getPrimes(int n) {
    std::vector<bool> isPrime(n + 1, true);
    std::vector<int> primes;
    for (int i = 2; i <= n; i++) {
        if (isPrime[i])
            primes.push_back(i);
        for (auto& prime : primes) {
            if (i * prime > n)
                break;
            isPrime[i * prime] = false;
            if (i % prime == 0)
                break;
        }
    }
    return primes;
}
