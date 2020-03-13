#include <bits/stdc++.h>

using namespace std;

struct Bip {
    int n,m; // #l, #r
    vector<vector<int>> g;
    vector<int> left;
    vector<bool> trk;

    Bip(int _n) : n(_n), m(_n) {
        init();
    }
    Bip(int _n, int _m) : n(_n), m(_m) {
        init();
    }
    void init() {
        g.resize(n);
        left.assign(m, -1);
        trk.assign(n, false);
    }
    inline void add(int l, int r) {
        assert(0 <= l && l < n);
        assert(0 <= r && r < m);
        g[l].emplace_back(r);
    }

    bool dfs(int l) {
        if (trk[l]) return false;
        trk[l] = true;
        for (int r: g[l]) {
            if (left[r] == -1 || dfs(left[r])) {
                left[r] = l;
                return true;
            }
        }
        return false;
    }
    int match() {
        int cnt = 0;
        for (int i = 0; i < n; i++) {
            fill(trk.begin(), trk.end(), false);
            if (dfs(i)) cnt++;
        }
        return cnt;
    }
};

// 网络流24题 最小路径覆盖问题
// DAG, match ensure (in/out)deg[v]<=1.
void solve() {
    int n,m;
    cin >> n >> m;
    Bip g(n);
    for (int _ = 0; _ < m; _++) {
        int x,y;
        cin >> x >> y;
        x--;y--;
        g.add(x,y);
    }
    int res = n - g.match();
    auto& L = g.left;
    vector<int> R(n,-1);
    for (int i = 0; i < n; i++) {
        if (L[i] != -1) {
            R[L[i]] = i;
        }
    }
    for (int i = 0; i < n; i++) {
        if (L[i]==-1) {
            int x = i;
            while (x != -1) {
                cout << x+1 << ' ';
                x = R[x];
            }
            cout << '\n';
        }
    }
    cout << res;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}
