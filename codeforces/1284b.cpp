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
    int n; cin >> n;
    vector<int> a,b;
    for (int i = 0; i < n; i++) {
        int m; cin >> m;
        bool isdec = true;
        int las = 1e8;
        int mi = 1e8, mx = -1e8;
        for (int _ = 0; _ < m; _++) {
            int x; cin >> x;
            isdec &= las>=x;
            las = x;
            mi = min(mi, x);
            mx = max(mx, x);
        }
        if (m==1 || isdec) {
            a.push_back(mi);
            b.push_back(mx);
        }
    }
    sort(b.begin(), b.end());
dbg(a,b);
    long long res = 1ll*n*n;
    for (int x: a) {
        int i = upper_bound(b.begin(), b.end(), x) - b.begin();
dbg(x,i);
        res -= i;
    }
    cout << res;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
