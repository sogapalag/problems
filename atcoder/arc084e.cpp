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
using ll=long long ;

// editorial method, start from (3,...,3), decreasing lexi (n)/2 times, since there are n-1 (3,.empty) uncnt
void solve() {
    int k,n;
    cin >> k >> n;
    if (k%2==0) {
        cout << (k/2) << ' ';
        for (int _ = 1; _ < n; _++) {
            cout << k << ' ';
        }
        return;
    }
    const ll LIM = 1e6;
    vector<ll> len = {1, k};
    while (len.back()<LIM) {
        ll x = (1+len.back())*k;
        len.emplace_back(x);
    }
    int m = len.size() - 1;
    vector<int> res;
    for (int i = n; i > m; i--) {
        res.emplace_back((k+1)/2);
    }
    int shift = max(0, n-m); // (3,empty), (3,3,empty), (3,3,3, empty)
    m = min(n,m);
    ll nth = (len[m]-shift+1)/2;
    assert(nth>0);
    dbg(m, nth);
    dbg(len);
    function<void(int,ll)> calc = [&](int d, ll i){
        assert(i < len[d]);
        res.emplace_back(1 + i/(len[d]/k));
        i %= (len[d]/k);
        assert(i <= len[d-1]);
        if (i == 0) return; // (..,empty) stop
        calc(d-1, i-1);
    };
    calc(m, nth-1);
    for (auto& x: res) {
        cout << x << ' ';
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
