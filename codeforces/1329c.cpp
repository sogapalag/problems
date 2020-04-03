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

// greedy chose heap.top as long as the chain valid
// when del a chain, note remain split more heaps. (they're indep, so by i inc order is fine)
// proof, if f(l) then f(i pass r), one can see first f(i), l->i, f(i still pass r)  
void solve() {
    int n,m;
    cin >> n >> m;
    const int MSK = 1<<n; 
    const int G = 1<<m; 
    vector<int> a(MSK);
    ll res = 0;
    for (int i = 1; i < MSK; i++) {
        cin >> a[i];
        res += a[i];
    }
    vector<int> sz(MSK, 1);
    for (int i = MSK/2-1; i >= 1; i--) {
        sz[i] += sz[i<<1] + sz[i<<1|1];
    }
    vector<int> p(MSK - G);
    vector<bool> del(MSK);
    auto ck = [&](int i){
        if (del[i]) return false;
        int x = i;
        while (x < G/2) {
            int l = 2*x;
            int r = 2*x+1;
            x = a[l]>a[r] ? l : r;
        }
dbg(i, x);
        assert(x < G);
        if (sz[x] == 1) {
            while (x > i) {
                del[x] = true;
                x /= 2;
            }
            del[i] = true;
            return false;
        }
dbg("?");
        return true;
    };
    function<void(int)> f = [&](int i){
        if (G/2 <= i && i < G) --sz[i];
        int l = 2*i;
        int r = 2*i+1;
        if (l >= MSK || (a[l]==0 && a[r]==0)) {
            a[i] = 0;
        } else {
            if (a[l] > a[r]) {
                a[i] = a[l]; f(l);
            } else {
                a[i] = a[r]; f(r);
            }
        }
    };
    int i = 1;
    for (auto& r: p) {
        while (!ck(i)) {
            i++;
        }
dbg(i, res);
        res -= a[i];
        f(r = i);
    }
    cout << res << "\n";
    for (auto& r: p) {
        cout << r << ' ';
    }cout << '\n';
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int T; cin >> T;
    for (int t = 0; t < T; t++) {
        solve();
    }
    return 0;
}
