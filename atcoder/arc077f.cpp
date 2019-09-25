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

// z[i] = len of lcp of s, s[i..]; lcp(longest common prefix)
vector<int> z_fn(const string& s) {
    int n = s.size();
    vector<int> z(n, 0);
    for (int i = 1, l = 0, r = 0; i < n; i++) {
        if (i <= r)
            z[i] = min(r-i+1, z[i-l]);
        while (i+z[i] < n && s[z[i]] == s[i+z[i]]) {
            z[i]++;
        }
        if (i+z[i]-1 > r) {
            l = i; r = i+z[i]-1;
        }
    }
    return z;
}

void f(string& s){
    auto z = z_fn(s);
    int n = s.size();
    int i = n/2 + 1;
    while (i < n) {
        if (z[i] == n-i) break;
        i++;
    }
    for (int j = 0; j < 2*i-n; j++) {
        s.push_back(s[j+n-i]);
    }
}

// max eq-suffix
int min_prefix(const string& s){
    int n = s.size();
    auto z = z_fn(s);
    for (int i = 1; i < n; i++) {
        if (z[i] == n-i) return i;
    }
    return n;
}

using ll=long long ;
using Freq=array<ll,26>;
Freq& operator+=(Freq& a, const Freq& b){
    for (int i = 0; i < 26; i++) {
        a[i] += b[i];
    }
    return a;
}
const long long INF = 0x3f3f3f3f3f3f3f3f;

// T = S[..k]
// S
// ST
// ST S
// STS ST
// STSST STS
void solve() {
    string s; cin >> s;
    f(s);
    s.resize(s.size()/2);
    int k = min_prefix(s);
    int n = s.size();
    dbg(s,k,n);

    vector<ll> fib = {k, n};
    vector<Freq> cnt(100);
    for (int i = 0; i < k; i++) {
        cnt[0][s[i]-'a']++;
    }
    for (int i = 0; i < n; i++) {
        cnt[1][s[i]-'a']++;
    }
    while (fib.back() < INF) {
        int n = fib.size();
        fib.emplace_back(fib[n-1] + fib[n-2]);
        for (int i = 0; i < 26; i++) {
            cnt[n][i] = cnt[n-1][i] + cnt[n-2][i];
        }
    }
    dbg(fib);
    dbg(cnt);

    int m = fib.size();
    dbg(m);
    dbg(cnt[m-1]);
    auto till = [&](ll r){
        Freq res = {};
        if (r <= 0) return res;
        for (int i = m-1; i >= 0; i--) {
            if (r < fib[i]) continue;
            res += cnt[i];
            r -= fib[i];
            dbg(i, res, r);
        }
        assert(r < n); // not k
        for (int i = 0; i < r; i++) {
            res[s[i]-'a']++;
        }
        return res;
    };

    ll l, r;
    cin >> l >> r;
    auto x = till(l-1);
    auto y = till(r);
    for (int i = 0; i < 26; i++) {
        cout << (y[i]-x[i]) << ' ';
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
