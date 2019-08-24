#include <bits/stdc++.h>

using namespace std;


void solve() {
    int n,m;
    cin >> n >> m;
    vector<pair<int, int>> a(m);
    for (int i = 0; i < m; i++) {
        int x,y;
        cin >> x >> y;
        a[i] = {x,y};
    }
    sort(a.begin(), a.end());
    int res = 0;
    int l = -1e8, r = 1e8;
    for (auto& p: a) {
        int x,y;
        tie(x,y) = p;
        l = max(l, x); r = min(r, y);
        if (l < r) continue;
        res++;
        l = x; r = y;
    }
    res++;
    cout << res;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
