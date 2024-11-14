#include <bits/stdc++.h>

class LCA {
public:
    std::vector<std::vector<int>> e, st;
    std::vector<int> dep, sz;
    int n, power;

    LCA(int _n) : n(_n), power(32 - __builtin_clz(n) - 1) {
        e.assign(n, std::vector<int>());
        st.assign(n, std::vector<int>(power + 1, -1));
        dep.assign(n, 0);
        sz.assign(n, 1);
    }

    void addEdge(int u, int v) {
        e[u].push_back(v);
        e[v].push_back(u);
    }

    void cal(int root) {
        dfs(root);
    }

    int lca(int u, int v) {
        if (dep[u] < dep[v])
            std::swap(u, v);
        int d = dep[u] - dep[v];
        for (int j = power; j >= 0; j--)
            if (d >> j & 1)
                u = st[u][j];
        if (u == v)
            return u;
        for (int j = power; j >= 0; j--)
            if (st[u][j] != st[v][j])
                u = st[u][j], v = st[v][j];
        return st[u][0];
    }

private:
    void dfs(int u, int p = -1) {
        if (p != -1)
            dep[u] = dep[p] + 1;
        st[u][0] = p;
        for (int j = 1; j <= power && (1 << j) <= dep[u]; j++) {
            st[u][j] = st[st[u][j - 1]][j - 1];
        }
        for (auto v : e[u]) {
            if (v != p) {
                dfs(v, u);
                sz[u] += sz[v];
            }
        }
    }
};
