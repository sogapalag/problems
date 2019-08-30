#include <bits/stdc++.h>

using namespace std;

using ll=long long ;
int n;
ll M;
ll& add(ll& r, ll x){
    return (r+=x)%=M;
}
ll X(ll r, ll x){
    return r*x%M;
}
ll& mult(ll& r, ll x){
    return (r*=x)%=M;
}
ll& mult_1(ll& r, ll x){
    return (r*=x)%=M-1;
}
ll mpow(ll x, int64_t e) {
    ll res = 1;
    for (; e; e >>= 1) {
        if (e & 1) mult(res, x);
        mult(x,x);
    }
    return res;
}
ll mpow_1(ll x, int64_t e) {
    ll res = 1;
    for (; e; e >>= 1) {
        if (e & 1) mult_1(res, x);
        mult_1(x,x);
    }
    return res;
}

const int N = 3123; 
ll pw[N],pw_1[N];
ll dp[N][N]; // [i] into j sets. consider append. similar to stirling
ll f[N]; // [i] each bit <=1. := sum_{j=0..=i} dp[i][j] (2^(n-i))^j 
ll fac[N], ifac[N], inv[N];

ll C(int n, int k) {
    if (n < k || k < 0) return 0;
    return fac[n] * ifac[n-k]%M * ifac[k]%M;
}

void pre() {
    memset(dp, 0, sizeof dp);
    dp[0][0] = 1; 
    for (int i = 1; i <= n; i++) {
        dp[i][0] = 1;
        for (int j = 1; j <= i; j++) {
            ll tmp = dp[i-1][j];
            add(dp[i][j], mult(tmp, j+1));
            add(dp[i][j], dp[i-1][j-1]);
        }
    }
    pw[0] = pw_1[0] = 1;
    for (int i = 1; i <= n; i++) {
        pw[i] = pw[i-1];
        mult(pw[i], 2);
        pw_1[i] = pw_1[i-1];
        mult_1(pw_1[i], 2);
    }
    memset(f, 0, sizeof f);
    for (int i = 0; i <= n; i++) {
        for (int j = 0; j <= i; j++) {
            ll tmp = pw[n-i];
            add(f[i], X(dp[i][j], mpow(tmp, j)));
        }
    }
    fac[0] = fac[1] = 1;
    ifac[0] = ifac[1] = 1;
    inv[1] = 1;
    for (int i = 2; i <= n; i++) {
        fac[i] = fac[i-1] * i % M;
        inv[i] = (M-M/i) * inv[M%i] % M;
        ifac[i] = ifac[i-1] * inv[i] % M;
    }
}

void solve() {
    cin >> n >> M;
    pre();
    ll Q = 0;
    for (int i = 1; i <= n; i++) {
        ll tmp = C(n,i) * f[i] %M * mpow(2, pw_1[n-i])%M;
        (i&1)? add(Q, tmp) : add(Q, M-tmp);
    }
    ll P = mpow(2, pw_1[n]);
    ll res = (P-Q+M) %M;
    cout << res;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
