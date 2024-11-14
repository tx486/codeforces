#include <bits/stdc++.h>

std::vector<bool> Bipartite(const std::vector<std::vector<int>>& e) {  // 染色法判断二分图
    int n = e.size();
    std::vector<int> color(n, -1);
    std::queue<int> q;
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        for (int v : e[u]) {
            if (color[v] == -1) {
                color[v] = color[u] ^ 1;
                q.push(v);
            } else if (color[v] == color[u]) {
                return {};
            }
        }
    }
    std::vector<bool> ans(n);
    for (int i = 0; i < n; i++) {
        ans[i] = color[i];
    }
    return ans;
}