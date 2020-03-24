#include <bits/stdc++.h>

using namespace std;
using ll=long long;

struct AhoCorasick {
    static const int N = 14;
    static const char A = 'a';
    struct Node {
        int ch[N];
        int fail;ll cnt;
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
    void add(const string& p, int val) {
        int x = 0;
        for (char c: p) {
            int k = c-A;
            if (!t[x].ch[k]) {
                t[x].ch[k] = t.size();
                t.emplace_back();
            }
            x = t[x].ch[k];
        }
        t[x].cnt += val;
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

#undef LOCAL
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
#define dbg(args...) 2020
#endif

const int L = 14; 
const int MSK = 1<<L; 
ll dp[MSK][1024];
int g[1024][L];
ll cnt[1024];


void solve() {
    int n; cin >> n;
    AhoCorasick ac;
    for (int _ = 0; _ < n; _++) {
        string t; int c;
        cin >> t >> c;
        ac.add(t,c);
    }
    ac.build();
    const int T = ac.t.size(); 
    {// prep graph
        for (int u = 0; u < T; u++) {
            //int x = u; ..suck
            for (int k = 0; k < L; k++) {
                int x = u;
                while (x && !ac.t[x].ch[k]) {
                    x = ac.t[x].fail;
                }
                g[u][k] = ac.t[x].ch[k];
dbg(u,k,g[u][k], x, ac.t[x].ch[k]);
            }
        }
        for (int u = 0; u < T; u++) {
            cnt[u] = ac.t[u].cnt;
dbg(cnt[u]);
        }
    }

    string s; cin >> s;
    n = s.size();
    memset(dp, 0xc0, sizeof dp);
    dp[0][0] = 0;
    // msk=prev ?s used char, u=trie_state 
    int las = -1;
    int ques = 0;
    for (int i = 0; i < n; i++) if(s[i]=='?') {
        ques++;
        vector<int> end(T); // u ->(s(las..i)) -> end[u]
        iota(end.begin(), end.end(), 0);
        vector<ll> sum(T); // cost in above path
        for (int j = las+1; j < i; j++) {
            int k = s[j]-'a';
            for (int u = 0; u < T; u++) {
                end[u] = g[end[u]][k];
                sum[u] += cnt[end[u]];
            }
        }
        for (int msk = 0; msk < MSK; msk++) if(__builtin_popcount(msk) == ques-1){
            for (int u = 0; u < T; u++) {
                for (int k = 0; k < L; k++) {
                    if (msk>>k&1) continue;
                    int v = g[end[u]][k];
                    dp[msk|1<<k][v] = max(dp[msk|1<<k][v], dp[msk][u] + sum[u] + cnt[v]);
                }
            }
        }
        las = i;
    }
    ll res = -1e18;
    {// las..n
        vector<int> end(T); // u ->(s(las..i)) -> end[u]
        iota(end.begin(), end.end(), 0);
        vector<ll> sum(T); // cost in above path
        for (int j = las+1; j < n; j++) {
            int k = s[j]-'a';
            for (int u = 0; u < T; u++) {
                end[u] = g[end[u]][k];
                sum[u] += cnt[end[u]];
            }
        }
        for (int msk = 0; msk < MSK; msk++)if(__builtin_popcount(msk)==ques){
            for (int u = 0; u < T; u++) {
                res = max(res, dp[msk][u] + sum[u]);
            }
        }
    }
    cout << res;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}
