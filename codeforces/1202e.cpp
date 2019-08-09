#include <bits/stdc++.h>

using namespace std;

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

void solve() {
    AhoCorasick pre, suf;
    string T; cin >> T;
    int n; cin >> n;
    for (int _ = 0; _ < n; _++) {
        string s; cin >> s;
        pre.add(s);
        reverse(s.begin(), s.end());
        suf.add(s);
    }
    pre.build(); suf.build();
    auto f = pre.query(T);
    reverse(T.begin(), T.end());
    auto g = suf.query(T);
    reverse(g.begin(), g.end());
    long long res = 0;
    for (int i = 0; i < (int)T.size()-1; i++) {
        res += (long long) f[i] * g[i+1];
    }
    cout << res;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
