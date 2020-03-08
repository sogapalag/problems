#include <bits/stdc++.h>

using namespace std;


void solve() {
    int n; cin >> n;
    vector<tuple<int, int, int>> g[2];
    for (int i = 0; i < n; i++) {
        int x,y;
        cin >> x >> y;
        g[x<y].emplace_back(x,y,i);
    }
    if (g[0].size() > g[1].size()) {
        cout << g[0].size() << '\n';
        sort(g[0].begin(), g[0].end(), [&](auto& u, auto& v){
            return get<1>(u) < get<1>(v);
        });
        for (auto& _: g[0]) {
            cout << get<2>(_) + 1 << ' ';
        }
    } else {
        cout << g[1].size() << "\n";
        sort(g[1].begin(), g[1].end(), [&](auto& u, auto& v){
            return get<1>(u) > get<1>(v);
        });
        for (auto& _: g[1]) {
            cout << get<2>(_) + 1 << ' ';
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}
