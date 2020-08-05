#include <bits/stdc++.h>

using namespace std;
using ll=long long;

const int N = 15;

int x[N], y[N], z[N];
ll a[N][1<<N]; // min dist of i-{msk}
ll b[N][1<<N];

void solve() {
    int n; cin >> n;
    const int MSK = 1<<n; 
    for (int i = 0; i < n; i++) {
        cin >> x[i] >> y[i] >> z[i];
    }
    auto prep = [&](auto& x, auto& a){
        for (int msk = 0; msk < MSK; msk++) {
            for (int i = 0; i < n; i++) {
                if (msk>>i&1) a[i][msk] = 0;
                else {
                    int res = abs(x[i]);
                    for (int j = 0; j < n; j++) {
                        if (msk>>j&1) res = min(res, abs(x[i] - x[j]));
                    }
                    a[i][msk] = res *1ll* z[i]; // ll
                }
            }
        }
    };
    prep(x,a); prep(y,b);
    vector<ll> res(n + 1, 1ll<<60);
    // u,v be two sets rail
    for (int tot = 0; tot < MSK; tot++) {
        int cnt = __builtin_popcount(tot);
        for (int u = tot; u >= 0; (u-=1)&=tot) {
            int v = tot^u;
            ll sum = 0;
            for (int i = 0; i < n; i++) {
                if (tot>>i&1) continue;
                sum += min(a[i][u], b[i][v]);
            }
            res[cnt] = min(res[cnt], sum);
            if (u==0) break;
        }
    }
    for (auto& x: res) {
        cout << x << '\n';
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}
