#include <bits/stdc++.h>

using namespace std;
using ll=long long;

ll dp[2][1<<7];

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

void solve() {
    int n, p, k;
    cin >> n >> p >> k;
    vector<int> a(n);
    for (auto& x: a) {
        cin >> x;
    }
    vector<vector<int>> g(n, vector<int>(p));
    for (auto& b: g) {
        for (auto& x: b) {
            cin >> x;
        }
    }
    vector<int> id(n);
    iota(id.begin(), id.end(), 0);
    sort(id.begin(), id.end(), [&](auto& u, auto& v){
        return a[u] > a[v];
    });
    
    auto maxi = [](ll& x, ll y){
        if (x < y) x = y;
    };
    const int MSK = 1<<p; 
    int crt = 0;
    for (int _ = 0; _ < n; _++) {
        int i = id[_];
        int x = a[i];
dbg(i,x);
        int nxt = crt ^ 1;
        memset(dp[nxt], 0, sizeof dp[nxt]);
        for (int msk = 0; msk < MSK; msk++) {
            int u = __builtin_popcount(msk);
            for (int j = 0; j < p; j++) {
                if (msk>>j&1) {
                    maxi(dp[nxt][msk], dp[crt][msk^(1<<j)] + g[i][j]);
                }
            }
            maxi(dp[nxt][msk], dp[crt][msk]); // skip... // damn, I should memcpy.
            // this imply we can add it to {k}
            if (u<=_ && _-u < k) {
                maxi(dp[nxt][msk], dp[crt][msk] + x);
            }
            dbg(msk,dp[crt][msk]);
        }
        crt ^= 1;
    }
    cout << dp[crt][MSK-1];
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}
