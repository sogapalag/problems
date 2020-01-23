#include <bits/stdc++.h>

using namespace std;
using ll=long long;

// when range [l, r), has property notP~P, want first P.
// when return r, means not found.
template <typename T>
T bs_first(T l, T r, function<bool (T)> f) {
    assert(l < r);
    T mid;
    while (l != r) {
        mid = l + (r-l)/2;
        if (f(mid)) {
            r = mid;
        }else {
            l = mid + 1;
        }
    }
    return r;
}

const int N = 64; 
ll c[N][N];
void prep() {
    c[0][0] = 1;
    for (int i = 1; i < N; i++) {
        c[i][0] = 1;
        for (int j = 1; j < N; j++) {
            c[i][j] = c[i-1][j-1] + c[i-1][j];
        }
    }
}
// [0..n) #bits_len=k
ll count_kbits(ll n, int k) {
    if (n==0||k<0) return 0;
    int i = 63 - __builtin_clzll(n);
    ll sum = c[i][k];
    return sum + count_kbits(n^1ll<<i, k-1);
}
// note from (n,2n] -> (n+1,2n+2]. add one more n<<1|1.  since note n is same 1s as n<<1
// => #(n,2n] ,k = #[0,n),k-1
void solve() {
    prep();
    ll n; int k;
    cin >> n >> k; k--;
    ll res = bs_first<ll>(1, 1e18, [&](ll x){
            return count_kbits(x, k) >= n;
            });
    cout << res;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}
