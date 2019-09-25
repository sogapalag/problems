#include <bits/stdc++.h>

using namespace std;
using ll=long long ;

void solve() {
    int n,m;
    cin >> n >> m;
    vector<int> a(n);
    for (auto& x: a) {
        cin >> x; x--;
    }
    vector<int> c(3*m); // indicate segment
    vector<int> d(3*m); // after-seg, previous profit add back
    ll base = 0;
    for (int i = 1; i < n; i++) {
        int x = a[i-1], y = a[i];
        if (x > y) y += m;
        base += y-x;
        if (y-x <= 1) continue;
        c[x+1]++; c[y]--; d[y] += y-x-1;
        c[x+1+m]++; c[y+m]--; d[y+m] += y-x-1;
    }
    int cnt = 0;
    ll v = base;
    ll res = base;
    for (int i = 0; i < 2*m; i++) {
        v -= cnt;
        res = min(res, v);
        cnt += c[i];
        v += d[i];
    }
    cout << res;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
