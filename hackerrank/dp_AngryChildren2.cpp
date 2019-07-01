#include <bits/stdc++.h>

using namespace std;


// +1 -1...< <= next time make clear helper lambda
void solve() {
    int n, k; cin >> n >> k;
    vector<int> a(n);
    for (auto& x: a) {
        cin >> x;
    }
    sort(a.begin(), a.end());
    vector<int> d(n);
    for (int i = 0; i < n; i++) {
        d[i] = a[i] - a[0];
    }
    using ll=long long;
    vector<ll> sum(n);
    sum[0] = 0;
    for (int i = 1; i < n; i++) {
        sum[i] = sum[i-1] + d[i];
    }
    auto f = [&](int i, int j){// original a[j..=i] picked diff
        return sum[j] - sum[i] - (ll)(j-i) * d[i];
    };
    ll crt = 0;
    for (int i = 0; i < k; i++) {
        crt += f(i, k-1); //sum[k-1] - sum[i-1] - (ll)(k-i) * d[i];
    }
    ll res = crt;
    for (int i = 0; i+k < n; i++) {
        crt -= f(i, i+k-1); 
        crt += (ll)(k)*(d[i+k] - d[i+1]) - f(i+1, i+k);
        res = min(res, crt);
    }
    cout << res;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
