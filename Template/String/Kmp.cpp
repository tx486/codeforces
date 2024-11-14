#include <bits/stdc++.h>
std::vector<int> nextArray(std::string& s) {
    int n = s.size();
    std::vector<int> nxt(n + 1);
    nxt[0] = -1;
    if (n > 0)
        nxt[1] = 0;
    for (int i = 2, j = 0; i <= n; i++) {
        while (j >= 0 && s[i - 1] != s[j]) j = nxt[j];
        nxt[i] = ++j;
    }
    return nxt;
}