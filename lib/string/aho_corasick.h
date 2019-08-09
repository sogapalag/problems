#include <bits/stdc++.h>

using namespace std;

// key idea
// fail/suffix-link of p[..i] : ->e[..j] which is longest suffix of p[..i]
// then in bfs/build or in query, follow DFA if there is a children move, else follow fail-link
//
// useful link
// http://web.stanford.edu/class/archive/cs/cs166/cs166.1166/lectures/02/Small02.pdf
// https://cp-algorithms.com/string/aho_corasick.html

// SNIPPETS_START aho_corasick
struct AhoCorasick {
    static const int N = 26;
    static const char A = 'a';
    struct Node {
        int ch[N];
        int fail, cnt;
        Node() {
            fill(ch, ch+N, 0);
            fail = 0;
            cnt = 0;
        }
    };

    vector<Node> t; //trie
    AhoCorasick() {
        t.reserve(200'005);
        t.emplace_back();
    }
    // add pattern
    void add(const string& p) {
        int x = 0;
        for (char c: p) {
            int k = c-A;
            if (!t[x].ch[k]) {
                t[x].ch[k] = t.size();
                t.emplace_back();
            }
            x = t[x].ch[k];
        }
        t[x].cnt++;
    }
    // build fail/suffix-link
    void build() {
        queue<int> q;
        for (int i = 0; i < N; i++) {
            if (t[0].ch[i])
                q.push(t[0].ch[i]);
        }
        while (!q.empty()) {
            int u = q.front(); q.pop();
            for (int i = 0; i < N; i++) {
                int v = t[u].ch[i];
                if (!v) continue;
                q.push(v);
                int f = t[u].fail;
                while (f && !t[f].ch[i]) {
                    f = t[f].fail;
                }
                f = t[v].fail = t[f].ch[i];
                t[v].cnt += t[f].cnt;
            }
        }
    }
    // res[i]: #match end with i.
    vector<int> query(const string& s) {
        int n = s.size();
        vector<int> res(n);
        int x = 0;
        for (int i = 0; i < n; i++) {
            int k = s[i] - A;
            while (x && !t[x].ch[k]) {
                x = t[x].fail;
            }
            x = t[x].ch[k];
            res[i] = t[x].cnt;
        }
        return res;
    }
};
// SNIPPETS_END
