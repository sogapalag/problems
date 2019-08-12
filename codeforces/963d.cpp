#include <bits/stdc++.h>

using namespace std;

#define LOCAL
string to_string(string s) { return '"' + s + '"'; }
string to_string(bool x) { return (x ? "T" : "F"); }
string to_string(const char* s) { return to_string((string)s); }
template <typename A, typename B>
string to_string(pair<A, B> p) { return "(" + to_string(p.first) + ", " + to_string(p.second) + ")"; }
template <typename V>
string to_string(V v) {
    bool f = true; string res = "[";
    for (const auto& x: v) {
        if (!f) res += ", ";
        f = false;
        res += to_string(x); } res += "]";
    return res;
}
void debug() { cerr << endl; }
template <typename H, typename... T>
void debug(H h, T... t) { cerr << " " << to_string(h); debug(t...); }
#ifdef LOCAL
#define dbg(args...) cerr<<"("<<#args<<") =", debug(args)
#else
#define dbg(args...) 2019
#endif

struct AhoCorasick {
    static const int N = 26;
    static const char A = 'a';
    int num = 0;
    struct Node {
        int ch[N];
        int fail, cnt;
        vector<int> ids;
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
    void add(const string& p, int i) {
        num++;
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
        t[x].ids.emplace_back(i);
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
                copy(t[f].ids.begin(), t[f].ids.end(), back_inserter(t[v].ids));
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

    vector<vector<int>> query_all(const string& s) {
        int n = s.size();
        vector<vector<int>> res(num);
        int x = 0;
        for (int i = 0; i < n; i++) {
            int k = s[i] - A;
            while (x && !t[x].ch[k]) {
                x = t[x].fail;
            }
            x = t[x].ch[k];
            for (int id: t[x].ids) {
                res[id].emplace_back(i);
            }
        }
        return res;
    }
};

void solve() {
    string text; cin >> text;
    int n; cin >> n;
    vector<int> a(n);
    vector<int> len(n);
    AhoCorasick AC;
    for (int i = 0; i < n; i++) {
        string pat;
        cin >> a[i] >> pat;
        len[i] = pat.size();
        AC.add(pat, i);
    }
    AC.build();
    auto pos = AC.query_all(text);

    for (int i = 0; i < n; i++) {
        int m = pos[i].size();
        int k = a[i];
        if (m < k) {
            cout << "-1\n"; continue;
        }
        int mi = 1e8;
        for (int j = k-1; j < m; j++) {
            mi = min(mi, pos[i][j] - pos[i][j-k+1]);
        }
        int res = mi + len[i];
        cout << res << "\n";
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
