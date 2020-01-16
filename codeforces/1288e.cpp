#include <bits/stdc++.h>

using namespace std;

template <typename T=int>
struct Fenwick {
    int n;
    vector<T> v;
    
    Fenwick(int size = 100005) : n(size), v(n+1, 0) {}
    inline void add(int p, T val) {
        for (; p <= n; p += (p&-p)) { v[p] += val; }
    }
    inline T query(int p) {
        T tmp = 0;
        for (; p > 0; p -= (p&-p)) { tmp += v[p]; }
        return tmp;
    }
    inline T query(int l, int r) {
        return query(r) - query(l-1);
    }
};

void solve() {
    int n,m;
    cin >> n >> m;
    // f trk occur, for query #>x
    // g trk last occur, for count #distinct in range
    Fenwick<int> f(n), g(m);
    vector<int> mi(n+1), mx(n+1);
    iota(mi.begin(), mi.end(), 0);
    iota(mx.begin(), mx.end(), 0);

    vector<int> pre(n+1);
    for (int i = 1; i <= m; i++) {
        int x; cin >> x;
        mi[x] = 1;
        if (!pre[x]) {
            mx[x] = max(mx[x], x + f.query(x, n));
            f.add(x, 1);
            g.add(i, 1);
        } else {
            mx[x] = max(mx[x], g.query(pre[x], i));
            g.add(pre[x], -1);
            g.add(i, 1);
        }
        pre[x] = i;
    }
    // virtual
    for (int x = 1; x <= n; x++) {
        if (!pre[x]) {
            mx[x] = max(mx[x], x + f.query(x, n));
        } else {
            mx[x] = max(mx[x], g.query(pre[x], m));
        }
    }
    for (int x = 1; x <= n; x++) {
        cout << mi[x] << ' ' << mx[x] << "\n";
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}
