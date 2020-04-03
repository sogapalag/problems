#include <bits/stdc++.h>

using namespace std;
using ll=long long;

// lower bound, WA, 
// |  |00|
// |00|  |
void __solve() {
    int n; cin >> n;
    vector<int> a(2*n);
    ll res = 0;
    int cnt = 0;
    for (int i = 0; i < 2*n; i++) {
        int y;
        cin >> a[i] >> y;
        if (y >= 2) {
            res += y-2; cnt++;
        } else res += 1-y;
    }
    res += abs(n-cnt);
    sort(a.begin(), a.end());
    for (int i = 0; i < 2*n; i++) {
        res += abs(a[i] - (i/2+1));
    }
    cout << res << '\n';
}

const int N = 100005; 
int a[N][2];
// min cut
void solve() {
    int n; cin >> n;
    ll res = 0;
    for (int i = 1; i <= 2*n; i++) {
        int x,y;
        cin >> x >> y;
        int xx = max(1, min(n, x));
        int yy = max(1, min(2, y));
        res += abs(x-xx);
        res += abs(y-yy);
        a[xx][yy-1]++;
    }
    for (int i = 1, s0=0,s1=0; i <= n; i++) {
        s0 += a[i][0]; --s0;
        s1 += a[i][1]; --s1;
        if (s0 > 0 && s1 < 0) {
            int x = min(s0, -s1);
            res += x;
            s0 -= x;
            s1 += x;
        }
        if (s0 < 0 && s1 > 0) {
            int x = min(-s0, s1);
            res += x;
            s0 += x;
            s1 -= x;
        }
        res += abs(s0) + abs(s1);
    }
    cout << res << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}
