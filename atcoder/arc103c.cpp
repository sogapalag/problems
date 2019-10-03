#include <bits/stdc++.h>

using namespace std;


void solve() {
    int n; cin >> n;
    vector<int> a(n);
    for (auto& x: a) {
        cin >> x;
    }
    vector<pair<int, int>> f[2];
    for (int j = 0; j < 2; j++) {
        map<int, int> mp;
        for (int i = j; i < n; i+=2) {
            mp[a[i]]++;
        }
        for (auto& p: mp) {
            f[j].emplace_back(p.second, p.first);
        }
        f[j].emplace_back(0, -1);
        sort(f[j].begin(), f[j].end(), greater<pair<int,int>>());
    }
    int mx;
    if (f[0][0].second != f[1][0].second) mx = f[0][0].first + f[1][0].first;
    else mx = max(f[0][0].first + f[1][1].first, f[0][1].first + f[1][0].first);
    int res = n - mx;
    cout << res;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
