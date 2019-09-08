#include <bits/stdc++.h>

using namespace std;


void solve() {
    int n; cin >> n;
    vector<pair<int, int>> a(n), b(n);
    for (int i = 0; i < n; i++) {
        int x,y;
        cin >> x >> y;
        a[i]={x,y};
    }
    for (int i = 0; i < n; i++) {
        int x,y;
        cin >> x >> y;
        b[i]={x,y};
    }
    vector<vector<int>> g(n);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (a[i].first<b[j].first && a[i].second<b[j].second)
                g[i].emplace_back(j);
        }
    }
    vector<bool> trk(n, false);
    vector<int> left(n, -1);
    function<bool(int)> dfs = [&](int l){
        if (trk[l]) return false;
        trk[l] = true;
        for (int r: g[l]) {
            if (left[r] == -1 || dfs(left[r])) {
                left[r] = l;
                return true;
            }
        }
        return false;
    };
    int cnt = 0;
    for (int i = 0; i < n; i++) {
        fill(trk.begin(), trk.end(), false);
        if (dfs(i)) cnt++;
    }
    cout << cnt;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
