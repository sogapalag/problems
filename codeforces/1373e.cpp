#include <bits/stdc++.h>

using namespace std;
using ll=long long;
const long long INF = 0x3f3f3f3f3f3f3f3f;

ll res[255][11];

ll f(ll x) {
    ll s = 0;
    for (char c: to_string(x)) s += c-'0';
    return s;
}

// the key is note x must be form
//   a9..99b  or  a9..98b (this form ensure not carry to 0..00)
void solve() {
    memset(res, 0x3f, sizeof res);
    for (int i = 0; i < 9; i++) {
        ll val = i;
        for (int j = 0; j < 17; j++) {
            for (int k = 0; k < 10; k++) {
                for (ll x: {val*10+k, (val-1)*10+k}) if(x>=0){
                //ll x = val*10 + k;
                ll sum = 0;
                for (int _ = 0; _ < 10; _++) {
                    sum += f(x+_);
                    if (sum > 155) break;
                    res[sum][_] = min(res[sum][_], x);
                }}
            }
            val = val*10+9;
        }
    }
    for (int i = 0; i <= 155; i++) {
        for (int j = 0; j < 10; j++) {
            if (res[i][j] == INF) res[i][j] = -1;
        }
    }
    int t; cin >> t;
    while (t--) {
        int s,k;
        cin >> s >> k;
        cout << res[s][k] << '\n';
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}
