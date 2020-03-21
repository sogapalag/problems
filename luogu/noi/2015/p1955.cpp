#include <bits/stdc++.h>

using namespace std;

struct Dsu {
    int n;
    vector<int> p;
    
    Dsu(int _n) : n(_n)
        , p(n)
    {
        init();
    }
    inline void init() {
        for (int i = 0; i < n; i++) {
            p[i] = i;
        }
    }
    inline int find(int x) {
        return p[x] == x ? x: p[x] = find(p[x]);
    }
    inline bool join(int x, int y) {
        x = find(x); y = find(y);
        if (x == y) return false;
        p[y] = x; return true;
    }
    inline bool check(int x, int y) {
        return find(x) == find(y);
    }
};

void solve() {
    int n; cin >> n;
    vector<int> Xs;
    vector<pair<int, int>> g[2];
    for (int _ = 0; _ < n; _++) {
        int x,y,e;
        cin >> x >> y >> e;
        g[e].emplace_back(x,y);
        Xs.push_back(x);
        Xs.push_back(y);
    }
    sort(Xs.begin(), Xs.end());
    Xs.erase(unique(Xs.begin(), Xs.end()), Xs.end());
    auto norm = [&](int x){
        return lower_bound(Xs.begin(), Xs.end(), x) - Xs.begin();
    };
    Dsu d(Xs.size());
    for (auto& _: g[1]) {
        int x,y;
        tie(x,y) = _;
        d.join(norm(x), norm(y));
    }
    for (auto& _: g[0]) {
        int x,y;
        tie(x,y) = _;
        if (d.check(norm(x), norm(y))) {
            cout << "NO\n";
            return;
        }
    }
    cout << "YES\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int T; cin >> T;
    for (int t = 0; t < T; t++) {
        solve();
    }
    return 0;
}
