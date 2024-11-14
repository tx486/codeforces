#include <bits/stdc++.h>

std::string minString(std::string& s) {
    int n = s.size(), i = 0;
    for (int j = 1, d = 0; j < n && i + d < n;) {
        if (s[i + d] < s[(j + d) % n]) {
            j += d + 1;
            d = 0;
        } else if (s[i + d] > s[(j + d) % n]) {
            i += d + 1;
            if (j <= i)
                j = i + 1;
            d = 0;
        } else
            d++;
    }
    return s.substr(i) + s.substr(0, i);
}