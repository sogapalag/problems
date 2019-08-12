#include <bits/stdc++.h>

using namespace std;

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
// when range [l, r), has property P~notP, want last P.
// when return l-1, means not found.
template <typename T>
T bs_last(T l, T r, function<bool (T)> f) {
    assert(l < r);
    T mid;
    while (l != r) {
        mid = l + (r-l)/2;
        if (f(mid)) {
            l = mid + 1;
        }else {
            r = mid;
        }
    }
    return r-1;
}
void solve() {
    RHash r;
    int n; cin >> n;
    string s; cin >> s;
    auto hsh = r.get_hash(s);
    int m = n/2;
    vector<int> len(m);// len[i]: i as center, max valid half-length. single=1
    for (int i = 0; i < m; i++) {
        int j = n-i-1;
        if (s[i] != s[j]) {
            len[i] = 0; continue;
        }
        int lim = i+2;
        len[i] = bs_last<int>(1, lim, [&](int x){
                return r.get_sub(hsh, i-x+1, i+x) == r.get_sub(hsh, j-x+1, j+x);
                });
    }
    vector<int> mx(m, -1);
    for (int i = 0; i < m; i++) {
        if (len[i] > 0) {
            int l = i-len[i]+1;
            mx[l] = max(mx[l], 2*len[i]-1);// when l, max valid length
        }
    }
    // res[i]: variant-prefix max, since valid iff the valid box[l,r] that l<=i
    for (int i = 1; i < m; i++) {
        mx[i] = max(mx[i], mx[i-1]-2); // whenever move right 1 step, before valid length -2
    }
    for (int i = 0; i < m; i++) {
        if (mx[i] <= 0) mx[i] = -1;
        cout << mx[i] << ' ';
    }
    if (n&1) cout << -1;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
