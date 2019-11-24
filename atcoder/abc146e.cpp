#include <bits/stdc++.h>

using namespace std;
using ll=long long;

// prefix, ar-al %k = r-l
// <=> ar-r = al-l and r-l<k
void solve() {
    int n,k;
    cin >> n >> k;
    map<int, vector<int>> mp;
    mp[0].push_back(0);
    int sum = 0;
    for (int i = 1; i <= n; i++) {
        int x; cin >> x;
        (sum += x) %= k;
        x = (sum-i)%k;
        (x+=k)%=k;
        mp[x].push_back(i);
    }

    ll res = 0;
    for (auto& _: mp) {
        auto& a = _.second;
        sort(a.begin(), a.end());
        int n = a.size();
        for (int i = 0; i < n; i++) {
            int l = a[i];
            int r = lower_bound(a.begin(), a.end(), l+k) - a.begin();
            res += r-i-1;
        }
    }
    cout << res;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
