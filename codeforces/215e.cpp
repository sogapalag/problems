#include <bits/stdc++.h>

using namespace std;
using ll=long long;
#define __up_loop(f) \
    for (int n = f.size(), i = 1; i < n; i++)\
        for (int j = i; (j += i) < n;)
#define __dn_loop(f) \
    for (int n = f.size(), i = n-1; i >= 1; i--)\
        for (int j = i; (j += i) < n;)

template <typename T>
inline void zeta(vector<T>& f) {
    __dn_loop(f) f[j] += f[i];
}
template <typename T>
inline void mobius(vector<T>& F) {
    __up_loop(F) F[j] -= F[i];
}
template <typename T>
inline void zeta_p(vector<T>& f) {
    __up_loop(f) f[i] += f[j];
}
template <typename T>
inline void mobius_p(vector<T>& F) {
    __dn_loop(F) F[i] -= F[j];
}

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

// main block is consider fix length=n
// note a period string has a min period. so vanilla cnt[x]=sum p|x #period=p
// so apply mobius
ll f(ll msk) {
    if (msk < 3) return 0;
    int n = 64 - __builtin_clzll(msk);
    vector<ll> cnt(n+1); // int pass, since halfed
    for (int i = 1; i <= n/2; i++) {
        if (n%i!=0)continue;
        ll prefix = msk>>(n-i);
        cnt[i] += prefix - (1ll<<(63-__builtin_clzll(prefix)));
        ll x = prefix;
        for (int j = i; j < n; j += i) {
            x <<= i; x |= prefix;
        }
        if (x <= msk) cnt[i]++;
    }
dbg(msk, n,cnt);
    mobius(cnt);
dbg(cnt);
    ll sum = 0;
    for (int i = 1; i <= n/2; i++) {
        if (n%i!=0)continue;
        sum += cnt[i];
    }
    // note vanilla cnt[n] = 0 = #(p=n) + #(p<n&&p|n)
    assert(sum == -cnt[n]); // so after apply we get #(p=n)
    return sum + f( (1ll<<(n-1)) - 1 );//nxt smaller length
}

void solve() {
    ll l,r;
    cin >> l >> r;
    cout << f(r)-f(l-1);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
