#include <bits/stdc++.h>

using namespace std;

const int MOD = 1e9+7; 

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
        const int N = 1006;
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
} R;

bool is[1003][1003];
ll res[1003];
// sum 1/n = log n
void solve() {
    int n; cin >> n;
    string s; cin >> s;
    auto hsh = R.get_hash(s);
    memset(is, 0, sizeof is);
    for (int i = 0; i < n; i++) {
        for (int j = i+1; j <= n; j++) {
            int d = j-i;
            int l = j, r = j+d;
            while (r <= n) {
                if (R.get_sub(hsh, i, j) == R.get_sub(hsh, l, r)) {
                    is[i][r] = 1;
                    l = r; r = l + d;
                } else {
                    break;
                }
            }
        }
    }
    memset(res, 0, sizeof res);
    auto ad = [&](ll& r, ll x){
        r += x; r %= MOD;
    };
    for (int i = 1; i <= n; i++) {
        if (is[0][i]) res[i] = 1;
        for (int j = 2; j < i; j++) {
            if (is[j][i])
                ad(res[i], res[j]);
        }
    }
    cout << res[n] << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int t; cin >> t;
    while(t--)solve();
    cout << endl;
}
