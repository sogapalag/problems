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
// when range [l, r), has property notP~P, want first P.
// when return r, means not found.
template <typename T>
T bs_first(T l, T r, function<bool (T)> f) {
    assert(l < r);
    T mid;
    while (l != r) {
        mid = l + (r-l)/2;
        if (f(mid)) {
            r = mid;
        }else {
            l = mid + 1;
        }
    }
    return r;
}
#define fi first
#define se second
void solve() {
    int n; cin >> n;
    vector<pair<int, int>> a(n);
    for (int i = 0; i < n; i++) {
        int x,y;
        cin >> x >> y;
        a[i] = {x,y};
    }
    sort(a.begin(), a.end());
    vector<int> mxr(n), pref(n);
    int cnt = 0;
    int r = -2e9;
    for (int i = 0; i < n; i++) {
        if (a[i].fi <= r) r = max(r, a[i].se);
        else {
            cnt++;
            r = a[i].se;
        }
        mxr[i] = r;
        pref[i] = cnt;
    }
dbg(mxr, pref);
    cnt = 0;
    int mx = 1;
    vector<int> ls; // segs [l..]  [l..] [l..]
    for (int i = n-1; i >= 0; i--) {
        int has = i>0 ? pref[i-1] : 0;
        if (!ls.empty()) {
            if (i == 0) has += ls.size();
            else {
                int r = mxr[i-1];
                int m = ls.size();
                int k = bs_first<int>(0, m, [&](int k){
                        return ls[k] <= r;
                        });
                has += k;
            }
        }
dbg(ls, has);
        mx = max(mx, has);
        int r = a[i].se;
        // update covered
        while (!ls.empty() && r >= ls.back()) {
            ls.pop_back();
        }
        ls.push_back(a[i].fi);
    }
    cout << mx << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int t; cin >> t;
    while(t--)solve();
    cout << endl;
}
