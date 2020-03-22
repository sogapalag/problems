#include <bits/stdc++.h>

using namespace std;

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

// greedy match
void solve() {
    int n,k;
    cin >> n >> k;
    vector<map<char,int>> trie; trie.emplace_back();
    vector<int> d; d.emplace_back();
    vector<int> dp; dp.emplace_back();
    vector<int> leaf; leaf.emplace_back();
    for (int _ = 0; _ < n; _++) {
        string s; cin >> s;
        int crt = 0;
        for (char c:s) {
            int& to = trie[crt][c];
            if (to == 0) {
                to = trie.size();
                trie.emplace_back();
                d.emplace_back(d[crt] + 1);
                dp.emplace_back();
                leaf.emplace_back();
            }
            crt = to;
        }
        leaf[crt]++;
    }
dbg(leaf, d);
    int res = 0;
    function<void(int)> dfs = [&](int u){
        int sum = 0;
        dp[u] += leaf[u];
        for (auto& _: trie[u]) {
            char c; int v;
            tie(c, v) = _;
            dfs(v);
            sum += dp[v]/k;
            dp[u] += dp[v];
        }
dbg(u, dp[u], sum);
        sum = dp[u]/k - sum; // #just at this layer matched
        res += sum * d[u];
dbg(res);
    };
    dfs(0);
    cout << res << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int T; cin >> T;
    for (int t = 1; t <= T; t++) {
        cout << "Case #" << t << ": ";
        solve();
    }
    return 0;
}
