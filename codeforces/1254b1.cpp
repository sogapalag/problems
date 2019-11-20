#include <bits/stdc++.h>

using namespace std;


void solve() {
    int n; cin >> n;
    vector<int> pos;
    for (int i = 0; i < n; i++) {
        int x; cin >> x;
        if (x) pos.emplace_back(i);
    }
    int k = pos.size();
    if (k <= 1) {
        cout << -1; return;
    }
    vector<int> ds;
    for (int d=2;d*d <= k;d++) {
        if (k%d==0) {
            ds.emplace_back(d);
            if (d*d!=k)ds.emplace_back(k/d);
        }
    }
    ds.emplace_back(k);
    sort(ds.begin(), ds.end());

    long long res = 1ll<<62;
    for (int d: ds) {
        long long tmp = 0;
        int s = 0;
        while (s < k) {
            for (int i = 0; i < d/2; i++) {
                tmp += pos[s + d-1-i] - pos[s+i];
            }
            s += d;
        }
        res = min(res, tmp);
    }
    cout << res;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
