#include <bits/stdc++.h>

using namespace std;


void solve() {
    int n, k;
    cin >> n >> k;
    map<int, int> mp;
    for (int _ = 0; _ < n; _++) {
        int x;cin >> x;
        mp[x]++;
    }
    if ((int)mp.size()<=k) {
        cout << 0; return;
    }
    vector<int> a;
    for (auto& p: mp) {
        a.emplace_back(p.second);
    }
    sort(a.begin(), a.end());
    int m = a.size();
    int res = 0;
    for (int i = 0; i < m-k; i++) {
        res += a[i];
    }
    cout << res;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
