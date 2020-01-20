#include <bits/stdc++.h>

using namespace std;

using ll=long long;
// in theoretical term, Z/M may called mobius transform/inversion on subset lattice
// O(n 2^n) Yates
#define __loop(f) \
    for (int i = 0, n = 31-__builtin_clz((int)f.size()), MSK = 1<<n; i < n; i++)\
        for (int msk = 0; msk < MSK; msk++)\
            if (msk>>i&1)

void solve() {
    int n; cin >> n;
    vector<vector<pair<int,int>>> g(n);
    for (int i = 0; i < n-1; i++) {
        int x,y;
        cin >> x >> y;
        x--;y--;
        g[x].emplace_back(y,i);
        g[y].emplace_back(x,i);
    }
    vector<int> pth;
    int T;
    function<bool(int,int)> dfs = [&](int u, int p){
        for (auto& e: g[u]) {
            int v,i;
            tie(v,i) = e;
            if (v==p) continue;
            pth.push_back(i);
            if (v == T) return true;
            if (!dfs(v, u)) pth.pop_back();
            else return true;
        }
        return false;
    };
    int m; cin >> m;
    vector<ll> cover(1<<m);
    for (int j = 0; j < m; j++) {
        int x,y;
        cin >> x >> y;
        x--;y--;
        T = y;
        pth.clear();
        dfs(x, -1);
        for (int i: pth) {
            cover[1<<j] |= 1ll<<i;
        }
    }
    __loop(cover) cover[msk] |= cover[msk^1<<i]; // O(m2^m) faster than dp O(n2^m)
    // IEP  I_i indicate i condition all white, we want cap(I_i^c)
    const int MSK = 1<<m; 
    ll res = 0;
    for (int msk = 0; msk < MSK; msk++) {
        int c = n-1 - __builtin_popcountll(cover[msk]);
        int sign = (__builtin_popcount(msk)&1) ? -1 : 1;
        res += sign * (1ll<<c);
    }
    cout << res;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}
