#include <bits/stdc++.h>

class Trie {
    struct Node {
        int freq{};
        Node* sons[26]{};
    }* root;

public:
    Trie() : root(new Node) {
    }
    void insert(std::string& s) {
        Node* u = root;
        for (auto& c : s) {
            if (!u->sons[c - 'a'])
                u->sons[c - 'a'] = new Node;
            u = u->sons[c - 'a'];
        }
        u->freq++;
    }
    int count(std::string& s) {
        Node* u = root;
        for (auto& c : s) {
            if (!u->sons[c - 'a'])
                return 0;
            u = u->sons[c - 'a'];
        }
        return u->freq;
    }
};