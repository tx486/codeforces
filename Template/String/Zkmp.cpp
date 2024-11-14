#include <bits/stdc++.h>

std::vector<int> zArray(std::string& s) {
    int n = s.size();
    std::vector<int> z(n + 1);
    z[0] = n;
    for (int i = 1, c = 0, r = 0, len; i <= n; i++) {
        len = r > i ? std::min(z[i - c], r - i) : 0;
        while (i + len < n && s[len] == s[i + len]) len++;
        if (i + len > r)
            c = i, r = i + len;
        z[i] = len;
    }
    return z;
}