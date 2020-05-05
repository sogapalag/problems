#include <bits/stdc++.h>

using namespace std;
using ll=long long;
const long long INF = 0x3f3f3f3f3f3f3f3f;
ll ckmul(ll x,ll y) {
    if (x > INF/y) return INF;
    return x*y;
}
ll ckadd(ll x,ll y) {
    if (x > INF-y) return INF;
    return x+y;
}
const int N = 100; 

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

// key(for large n): pref/suff are "a..a", middle-len <= 100
//  thus become small n problem
// then brute-force decide each i:0..n, each s[i]=c, sum of valid for each len
// Caution!: a naive method decide end to middle by dp, is wrong.
//   e.g. cac < cc
void solve() {
    ll l,n,k;
    cin >> l >> n >> k;
    if (k <= n) {
        cout << k << '\n'; return;
    }
    ll res = 0;
    if (n > N) {
        ll x = (n-N)/2*2;
        res += x;
        n -= x; k -= x;
    }
    vector<ll> dp(n+1); // dp[n]:=#valid with len<=n, include empty
    dp[0] = 1, dp[1] = l+1;
    for (int i = 2; i <= n; i++) {
        dp[i] = ckadd(l+1, ckmul(dp[i-2], l));
    }
    if (k >= dp[n]) {
        cout << "0\n"; return;
    }
    vector<int> s(n);
    // l^e
    auto calc = [&](int len){
        ll res = 1;
        for (int i = 0; i < (len+1)/2; i++) {
            if (s[i]&&s[len-i-1] && s[i]!=s[len-i-1]) return 0ll;
            if (!s[i] && !s[len-i-1]) res = ckmul(res, l);
        }
        return res;
    };
    for (int i = 0; k > 0 && i < n; i++) {
        for (int c = 1; c <= l; c++) {
            ll sum = 0;
            s[i] = c;
            for (int len = i+1; len <= n; len++) {
                sum = ckadd(sum,calc(len));
            }
            dbg(i, c, k, sum);
            if (k <= sum) {
                break;
            }
            s[i] = 0;
            k -= sum;
        }
        //if (k==1 && calc(i+1)) break;
        // -= now
        k -= calc(i+1);
        if (!k) break; // redundent with check k>0
    }
    while (!s.back()) {
        s.pop_back();
    }
    res += s.size();
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
