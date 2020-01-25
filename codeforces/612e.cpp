#include <bits/stdc++.h>

using namespace std;


void solve() {
    int n; cin >> n;
    vector<int> a(n);
    for (auto& x: a) {
        cin >> x; x--;
    }
    vector<bool> trk(n);
    vector<vector<int>> g[2];
    for (int i = 0; i < n; i++) {
        if (!trk[i]) {
            vector<int> c;
            for (int x = i; !trk[x]; x = a[x]) {
                c.push_back(x); trk[x] = 1;
            }
            g[c.size()&1].push_back(c);
        }
    }

    if (g[0].size()&1) {
        cout << -1; return;
    }
    sort(g[0].begin(), g[0].end(), [&](auto& u, auto& v){
        return u.size() < v.size();
    });
    vector<int> res(n,-1);
    while (!g[0].empty()) {
        auto p = g[0].back(); g[0].pop_back();
        auto q = g[0].back(); g[0].pop_back();
        if (p.size() != q.size()) {
            cout << -1; return;
        }
        // pair up  \/\/\/
        for (int _ = 0; _ < (int)p.size(); _++) {
            int x = p[_];
            int y = q[_];
            int z = p[(_+1)%p.size()];
            res[x] = y;
            res[y] = z;
        }
    }
    for (auto& p: g[1]) {
        // 0 2 4 6 1 3 5 ->
        for (int _ = 0; _ < (int)p.size(); _++) {
            int x = p[_];
            int y = p[(_ + p.size()/2 + 1)%p.size()];
            res[x] = y;
        }
    }
    for (auto& x: res) {
        cout << x+1 << ' ';
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}
