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
#define dbg(args...) 2019
#endif

void solve() {
    int n, r;
    cin >> n >> r;
    vector<pair<int, int>> po, ne;
    for (int _ = 0; _ < n; _++) {
        int x, y;
        cin >> x >> y;
        if (y >= 0) po.emplace_back(x, y);
        else ne.emplace_back(x, y);
    }
    sort(po.begin(), po.end());
    int cnt = 0;
    for (auto& p: po) {
        int x, y;
        tie(x, y) = p;
        if (r >= x) {
            cnt++;
            r += y;
        }
    }
    // for negtive, by potential end time
    sort(ne.begin(), ne.end(), [&](auto& u, auto& v){
        return u.first+u.second > v.first+v.second;
    });
    dbg(ne);
    const int INF = 0x3f3f3f3f;
    vector<int> dp(r+1, -INF);
    dp[r] = 0;
    for (auto& p: ne) {
        int x, y;
        tie(x, y) = p;
        for (int i = 0; i <= r; i++) {
            if (dp[i] < 0 || i < x || i+y < 0) continue;
            dp[i+y] = max(dp[i+y], dp[i]+1);
        }
        dbg(dp);
    }
    int res = 0;
    for (int i = 0; i <= r; i++) {
        res = max(res, dp[i]);
    }
    res += cnt;
    cout << res;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
