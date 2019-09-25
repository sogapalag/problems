#include <bits/stdc++.h>

using namespace std;

using ll=long long ;
const int L = 60; 



void solve() {
    int n; cin >> n;
    vector<ll> a(n);
    vector<int> b(n);
    for (auto& x: a) {
        cin >> x;
    }
    for (auto& x: b) {
        cin >> x;
    }
    map<ll, vector<int>> mp;
    for (int i = 0; i < n; i++) {
        mp[a[i]].emplace_back(b[i]);
    }
    int cnt = 0;
    ll sum = 0;
    set<ll> cover;
    for (auto rit = mp.rbegin(); rit != mp.rend(); rit++) {
        auto msk = rit->first;
        auto& v = rit->second;
        bool y = false;
        if (v.size() >= 2) y = true;
        if (!y) {
            for (const auto& x: cover) {
                if ((msk&x) == msk) {
                    y |= true; break;
                }
            }
        }
        if (y) {
            cover.insert(msk);
            for (auto& x: v) {
                cnt++;
                sum += x;
            }
        }
    }
    if (cnt < 2) sum = 0;
    cout << sum;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
