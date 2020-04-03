#include <bits/stdc++.h>

using namespace std;
using ll=long long;

// so sleepy, didn't do well
void solve() {
    int n,m;
    cin >> n >> m;
    vector<int> len(m);
    for (auto& x: len) {
        cin >> x;
    }
    vector<ll> sum(m + 1);
    for (int i = m-1; i >= 0; i--) {
        sum[i] = sum[i+1] + len[i];
    }
    if (sum[0] < n) {
        cout << -1; return;
    }
    vector<int> p(m);
    iota(p.begin(), p.end(), 0);
    int r = len[0]; // the rightmost can put new
    for (int i = 1; i < m; i++) {
        p[i] = max(p[i], p[i-1]+1); // +1
        p[i] = max((ll)p[i], n - sum[i]); // at least for remain no hole
        if (p[i] > r) {
            cout << -1; return;
        }
        // note we take as less as possible for p
        // > boarder
        if (p[i] + len[i] > n) {
            cout << -1; return;
        }
        r = max(r, p[i] + len[i]);
    }
    for (auto& x: p) {
        cout << x+1 << ' ';
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}
