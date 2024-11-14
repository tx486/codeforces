#include <bits/stdc++.h>

class AcMatch {
public:
    AcMatch(int MAXSIZE) {
        tr.assign(MAXSIZE + 1, std::vector<int>(26, 0));
        isEnd.assign(MAXSIZE + 1, false);
        fail.assign(MAXSIZE + 1, 0);
        freq.assign(MAXSIZE + 1, 0);
        cnt = 0;
    }
    void insert(std::string& s) {
        int u = 0;
        for (auto& c : s) {
            if (!tr[u][c - 'a'])
                tr[u][c - 'a'] = ++cnt;
            u = tr[u][c - 'a'];
        }
        isEnd[u] = true;
    }
    int count(std::string& s) {
        int u = 0;
        for (auto& c : s) u = tr[u][c - 'a'];
        return freq[u];
    }
    int next(int u, char c) {
        int v = tr[u][c - 'a'];
        freq[v]++;
        return v;
    }
    bool alert(int u) {
        return isEnd[u];
    }
    int size() {
        return cnt;
    }
    void set_fail() {
        std::deque<int> q;
        for (int i = 0; i < 26; i++)
            if (tr[0][i])
                q.push_back(tr[0][i]);
        while (!q.empty()) {
            int u = q.front();
            q.pop_front();
            for (int i = 0; i < 26; i++) {
                int v = tr[u][i];
                if (v) {
                    fail[v] = tr[fail[u]][i];
                    q.push_back(v);
                } else
                    tr[u][i] = tr[fail[u]][i];
            }
        }
        for (int i = 1; i <= cnt; i++) isEnd[i] = isEnd[i] | isEnd[fail[i]];
    }
    void cal_freq() {
        std::vector<std::vector<int>> e(cnt + 1, std::vector<int>());
        for (int i = 1; i <= cnt; i++) e[fail[i]].push_back(i);
        auto dfs = [&](auto self, int u) -> void {
            for (auto v : e[u]) {
                self(self, v);
                freq[u] += freq[v];
            }
        };
        dfs(dfs, 0);
    }

private:
    std::vector<std::vector<int>> tr;
    std::vector<bool> isEnd;
    std::vector<int> fail, freq;
    int cnt;
};