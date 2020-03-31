#include <bits/stdc++.h>

using namespace std;
using ll=long long;

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

// one-way -> shortest
// note optim is  ->FASTs -> MIDs -> SLOWs
// so we can focus on each after-use some FASTs, two args matter (t,n)
//  0 1 ,... n,  i.e. decide create some MIDs make profit under limit t.
// it's optim to build MID at first unachievable station.
// a naive way might O(m^3) dp. dp[i][k] in first i segs, build extra k MIDs.
// another key observation: whenever we build a MID, it's corresponding to a profit with it.
//   i.e.  [M . . .]  M is build, . . .are achievable by it.
//   for each seg, the profit is monotonic.
// so now we have (m-1) monotonic profit arrays. we can just merge into one array, pick greatest k-m.
//   since all-monotonic ensure one-monotonic, i.e. valid, its seg-prev was chosen.
void solve() {
    int _n,m,k;
    cin >> _n >> m >> k;
    ll FAST, MID, SLOW;
    cin >> SLOW >> FAST >> MID;
    ll T; cin >> T;
    vector<int> a(m);
    for (auto& x: a) {
        cin >> x; x--;
    }
    vector<int> candi;
    ll res = 0;
    for (int i = 1; i < m; i++) {
        ll t = T - a[i-1]*FAST;
        if (t <= 0) break;
        ll n = a[i]-a[i-1];
dbg(i, t, n);
        res += (n*FAST <= t);
        for (int j = 0, l = 0; j <= k-m; j++) {
            if (t < 0) break;
            ll r = t / SLOW + l;
            r = min(r, n-1);
            if (j == 0) res += r-l;
            else candi.push_back(r-l+1);
            t -= (r+1-l) * MID;
            l = r+1;
            if (l == n) break;
        }
    }
    sort(candi.begin(), candi.end(), greater<int>());
dbg(candi);
    while (candi.size() < k-m) {
        candi.push_back(0);
    }
    for (int _ = 0; _ < k-m; _++) {
        res += candi[_];
    }
    cout << res << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}
