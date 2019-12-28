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
using ll=long long;
const int N = 1e6+10; 
pair<ll,int> dp[N];

// Lagrange, max L(x) = f(x) - c[h(x) - b]
// for optim, x*(c), h(x*(c)) = h(c) monotic dec.
// bs find c s.t. h(c) = b.
//
// a illustrated way, is view relax operaion, with cost for doing once.
//   this relax op should make dp concave. i.e. could do naive greedy-dp.?
//   @@NOT SURE CORRECTNESS. what's the rigorious argument?
void solve() {
    int n,k,l;
    cin >> n >> k >> l;
    string s; cin >> s;
    vector<bool> a(n);
    for (int i = 0; i < n; i++) {
        a[i] = s[i]>'Z';
    }
    vector<int> sum(n+1);
    for (int i = 1; i <= n; i++) {
        sum[i] = sum[i-1] + a[i-1];
    }

    // base dp, max elimate #1. suppose one op elimate all
    auto ck = [&](int c){
        dp[0] = {0, 0};
        for (int i = 1; i <= n; i++) {
            //dp[i] = dp[i-1];
            //dp[i].first += a[i];
            int j = max(0, i-l);
            dp[i] = max(dp[i-1], {dp[j].first + sum[i]-sum[j] - c, dp[j].second - 1});
        }
dbg(c, dp[n].second);
        return -dp[n].second <= k;
    };

    ll res = n/2;
    int cost = bs_first<int>(0, n+1, ck);
dbg(cost);
    // Caution, sum[n]-max_elimate
    ck(cost); res = min(res, sum[n] - (dp[n].first + 1ll*cost*k));

    for (int i = 0; i < n; i++) {
        a[i] = !a[i];
    }
    for (int i = 1; i <= n; i++) {
        sum[i] = sum[i-1] + a[i-1];
    }
    cost = bs_first<int>(0, n+1, ck);
    ck(cost); res = min(res, sum[n] - (dp[n].first + 1ll*cost*k));
dbg(cost);
    cout << res;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
