#include <bits/stdc++.h>

template <class T>
class MaxFlow {
public:
    struct _Edge {
        int u;
        int v;
        T cap;
        T flow;
    };
    MaxFlow() {
    }
    MaxFlow(int _n) {
        init(_n);
    }
    void init(int _n) {
        n = _n;
        e.clear();
        g.assign(n, {});
        cur.resize(n);
        h.resize(n);
    }
    void addEdge(int u, int v, T c) {
        g[u].push_back(e.size());
        e.emplace_back(v, c);
        g[v].push_back(e.size());
        e.emplace_back(u, 0);
    }
    T flow(int s, int t) {
        T ans = 0;
        while (bfs(s, t)) {
            cur.assign(n, 0);
            ans += dfs(s, t, std::numeric_limits<T>::max());
        }
        return ans;
    }

    std::vector<bool> minCut() {
        std::vector<bool> c(n);
        for (int i = 0; i < n; ++i) c[i] = (h[i] != -1);
        return c;
    }
    std::vector<_Edge> edges() {
        std::vector<int> a;
        for (int i = 0; i < (int)e.size(); i += 2) {
            Edge x;
            x.u = e[i + 1].v;
            x.v = e[i].v;
            x.cap = e[i].cap + e[i + 1].cap;
            x.flow = e[i + 1].cap;
            a.push_back(x);
        }
        return a;
    }

private:
    struct Edge {
        int v;
        T cap;
        Edge(int _v, T _cap) : v(_v), cap(_cap) {
        }
    };
    int n;
    std::vector<Edge> e;
    std::vector<std::vector<int>> g;
    std::vector<int> cur, h;
    bool bfs(int s, int t) {
        h.assign(n, -1);
        std::queue<int> q;
        h[s] = 0;
        q.push(s);
        while (q.size()) {
            const int u = q.front();
            q.pop();
            for (int i : g[u]) {
                auto [v, c] = e[i];
                if (c > 0 && h[v] == -1) {
                    h[v] = h[u] + 1;
                    if (v == t)
                        return true;
                    q.push(v);
                }
            }
        }
        return false;
    }
    T dfs(int u, int t, T f) {
        if (u == t)
            return f;
        auto r = f;
        for (int &i = cur[u]; i < (int)g[u].size(); ++i) {
            const int j = g[u][i];
            auto [v, c] = e[j];
            if (c > 0 && h[v] == h[u] + 1) {
                auto a = dfs(v, t, std::min(r, c));
                e[j].cap -= a;
                e[j ^ 1].cap += a;
                r -= a;
                if (r == 0)
                    return f;
            }
        }
        if (r == f)
            h[u] = -1;
        return f - r;
    }
};