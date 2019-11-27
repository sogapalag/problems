#include <bits/stdc++.h>

using namespace std;

template <typename T=int>
struct Fenwick2d {
    int n, m;
    vector<vector<T>> g;

    Fenwick2d(int _n, int _m) : n(_n), m(_m), g(n+1, vector<T>(m+1, 0)) {}
    inline void add(int x, int y, T val) {
        for (; x <= n; x += (x&-x)) {
            for (int j = y; j <= m; j += (j&-j)) {
                g[x][j] += val;
            }
        }
    }
    // 1-based [1,1..x,y] <=> 0-based [0,0..x,y)
    inline T query(int x, int y) {
        T sum = 0;
        for (; x > 0; x -= (x&-x)) {
            for (int j = y; j > 0; j -= (j&-j)) {
                sum += g[x][j];
            }
        }
        return sum;
    }
    // 1-based (l..r] <=> 0-based [l..r)
    inline T query(int xl, int yl, int xr, int yr) {
        return query(xr, yr) - query(xl, yr) - (query(xr, yl) - query(xl, yl));
    }
};

template <typename T>
struct RASQ2d {
    int n, m;
    Fenwick2d<T> diff;

    RASQ2d(int _n, int _m) : n(_n), m(_m), diff(n, m) {}

    inline void add(int xl, int yl, int xr, int yr, T val) {
        diff.add(xl, yl, val);
        diff.add(xl, yr, -val);
        diff.add(xr, yl, -val);
        diff.add(xr, yr, val);
    }
    inline T query(int x, int y) {
        return diff.query(x, y);
    }
};

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
using Token = array<int,4>;
// although AC, better replace fenwick +- to ^, and rng64 to hash
void solve() {
    int n,m,q;
    cin >> n >> m >> q;
    RASQ2d<int> ra(n,m);
    map<Token, int> mp;
    while (q--) {
        int op,x,y,u,v;
        cin >> op >> x >> y >> u >> v;
        if (op == 1) {
            Token to = {x,y,u,v};
            mp[to] = rng();
            ra.add(x,y,u+1,v+1, mp[to]);
        } else if (op == 2) {
            Token to = {x,y,u,v};
            ra.add(x,y,u+1,v+1, -mp[to]);
        } else {
            bool res = ra.query(x,y) == ra.query(u,v);
            cout << (res?"Yes":"No") << "\n";
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
