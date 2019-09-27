#include <bits/stdc++.h>

using namespace std;


void solve() {
    int n, W;
    cin >> n >> W;
    map<int, int> dp;
    dp[0] = 0;
    for (int _ = 0; _ < n; _++) {
        int w,v;
        cin >> w >> v;
        vector<pair<int, int>> a;
        for (auto& p: dp) {
            if (p.first + w > W) break;
            a.emplace_back(p.first+w, p.second+v);
        }
        for (auto& p: a) {
            if (dp.find(p.first)!=dp.end()) {
                dp[p.first] = max(dp[p.first], p.second);
            } else {
                dp[p.first] = p.second;
            }
        }
    }
    int res = 0;
    for (auto& p: dp) {
        res = max(res, p.second);
    }
    cout << res;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
