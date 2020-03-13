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

// 网络流24题 魔术球问题
// almost same as p2764, DAG, min-path-cover
void solve() {
    int n; cin >> n;
    const int N = 1567 + 1; // f(55)=1567
    Bip g(N);
    int match = 0;
    int i = 2;
    for (; i < N; i++) {
        for (int x = 1; x*x < 2*i; x++) {
            if (x*x-i<=0) continue;
            g.add(i, x*x-i); // i-> since each time we push flow related to i
        }
        fill(g.trk.begin(), g.trk.end(), false);
        if (g.dfs(i)) match++;
        if (i-match > n) break;
    }
    n = i-1;
    cout << n << "\n";
    auto& L = g.left;
    vector<int> R(n,-1);
    for (int i = 1; i <= n; i++) {
        if (L[i] != -1) {
            R[L[i]] = i;
        }
    }
    for (int i = 1; i <= n; i++) {
        if (R[i]==-1) {
            int x = i;
            while (x != -1) {
                cout << x << ' ';
                x = L[x];
            }
            cout << '\n';
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}
