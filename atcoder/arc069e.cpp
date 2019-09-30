#include <bits/stdc++.h>

using namespace std;
using ll=long long;

// take from large-idx among largests.
void solve() {
    int n; cin >> n;
    map<int,set<int>> mp;
    for (int i = 0; i < n; i++) {
        int x; cin >> x;
        mp[x].insert(i);
    }
    vector<ll> res(n, 0);
    int sz = 0;
    int i = n;
    for (auto rit = mp.rbegin(); rit != mp.rend(); rit++) {
        auto &ids = rit->second;
        auto j = next(rit);
        sz += ids.size();
        int pre = j==mp.rend()?0:j->first;
        int d = rit->first - pre;
        i = min(i, *ids.begin());
        res[i] += 1ll*d*sz;
    }
    for (auto& x: res) {
        cout << x << ' ';
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
