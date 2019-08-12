#include <bits/stdc++.h>

using namespace std;

// SNIPPETS_START rolling_hash
using ll=long long;
// Rolling Hash
struct RHash {
    const ll R = 843823891, iR = 1040004855;
    const ll M = 1637348371;
    vector<ll> a;
    vector<ll> pw;
    vector<ll> ipw;

    RHash() {
        assert(mul(R, iR) == 1);
        a.resize(256);
        iota(a.begin(), a.end(), 42);
        const int N = 1'000'006;
        pw.resize(N); ipw.resize(N);
        pw[0] = 1; ipw[0] = 1;
        for (int i = 1; i < N; i++) {
            pw[i] = mul(pw[i-1], R);
            ipw[i] = mul(ipw[i-1], iR);
        }
    }

    inline ll add(ll x, ll y) {
        return (x+y) %M;
    }
    inline ll sub(ll x, ll y) {
        return (x-y + M) %M;
    }
    inline ll mul(ll x, ll y) {
        return (x*y) %M;
    }

    vector<ll> get_hash(const string& s) {
        int n = s.size();
        vector<ll> sum(n+1);
        sum[0] = 0;
        for (int i = 0; i < n; i++) {
            sum[i+1] = add(sum[i], mul(pw[i], a[s[i]]));
        }
        return sum;
    }
    // s[l..r)
    ll get_sub(const vector<ll>& sum, int l, int r) {
        return mul(sub(sum[r], sum[l]), ipw[l]);
    }
};
// SNIPPETS_END

template <typename T>
T t_pow(T x, int64_t e) {
    RHash r;
    T res = 1;
    for (; e; e >>= 1) {
        if (e & 1) res = r.mul(res, x);
        x = r.mul(x,x);
    }
    return res;
}

int main() {
    const ll R = 843823891;
    const ll M = 1637348371;
    
    ll x = R, e = M - 2;
    ll inv = t_pow<ll>(x, e);
    cout << inv;
    ll rem = inv*R % M;
    cout << rem;
    assert(rem == 1);
}
