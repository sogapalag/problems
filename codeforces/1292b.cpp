#include <bits/stdc++.h>

using namespace std;
using ll=long long;
const long long INF = 0x3f3f3f3f3f3f3f3f;
using pl = pair<ll,ll>;
void solve() {
    ll x0,y0, kx,ky, bx,by;
    cin >> x0 >> y0 >> kx >> ky >> bx >> by;
    ll xs, ys, T;
    cin >> xs >> ys >> T;
    vector<pl> a;
    while (true) {
        a.emplace_back(x0, y0);
        x0 = x0*kx + bx;
        y0 = y0*ky + by;
        if (x0 > xs+T) break;
        if (y0 > ys+T) break;
    }
    int n = a.size();
    assert(n < 100);
    vector<ll> d(n);
    for (int i = 1; i < n; i++) {
        d[i] = abs(a[i].first - a[i-1].first) + abs(a[i].second - a[i-1].second);
    }
    vector<ll> sum(n);
    for (int i = 1; i < n; i++) {
        sum[i] = sum[i-1] + d[i];
    }
    int res = 0;
    for (int i = 0; i < n; i++) {
        ll x,y;
        tie(x,y) = a[i];
        ll t = abs(x-xs) + abs(y-ys);
        if (t > T) continue;
        int cnt = 1;
        ll cx,cy;
        cx = xs, cy = ys;
        res = max(res, cnt);
        for (int j = 0; j < n; j++) {
            ll dt0 = sum[max(i,j)] - sum[min(i,j)];
            if (t + dt0 > T)continue;
            for (int k = 0; k < n; k++) {
                ll dt1 = sum[max(j,k)] - sum[min(j,k)];
                if (t + dt0 + dt1 <= T) {
                    int c = max({i,j,k}) - min({i,j,k}) + 1;
                    res = max(res, c);
                }
            }
        }
    }
    cout << res;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}
