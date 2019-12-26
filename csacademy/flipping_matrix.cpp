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

void solve() {
    int n; cin >> n;
    Bip bip(n);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            int x; cin >> x;
            if (x) bip.add(i, j);
        }
    }
    if (bip.match() < n) {
        cout << -1; return;
    }

    auto p = bip.left;
    vector<bool> trk(n);
    vector<pair<int, int>> res;
    for (int i = 0; i < n; i++) {
        if (p[i]==i)continue;
        if (trk[i]) continue;
        int x = i; trk[x] = true;
        while (!trk[p[x]]) {
            res.emplace_back(x, p[x]);
            x = p[x]; trk[x] = true;
        }
    }
    reverse(res.begin(), res.end());
    for (auto& _: res) {
        int x,y;
        tie(x,y)=_;
        x++;y++;
        cout << "C "<< x<<' '<<y << "\n";
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
