#include <bits/stdc++.h>

using namespace std;
// iterative version.
// TODO std::variant, to save half space

// SNIPPETS_START persistent_dsu_iterative
// time: O(m L^2 a(n))
// space: exactly S = 2N + 2*(#successful-join)*(L+1)
struct PersistentDsu {
    using Ptr = int;
    using Index = int;
    int n, L, N;
    vector<Ptr> ch[2];
    vector<Index> pa;
    vector<int> rk;
    Ptr vc = 1;
    PersistentDsu(int _n) : n(_n) {
        L = 1; N = 2;
        while (N < n) ++L, N <<= 1;
        int S = 2*N + 2*n*(L+1);
        ch[0].resize(S);
        ch[1].resize(S);
        pa.resize(S);
        rk.resize(S);
        build();
    }
    void build() {
        for (int i = 2*N-1; i >= N; i--) {
            pa[i] = i-N;
        }
        for (int i = N-1; i >= 1; i--) {
            ch[0][i] = i<<1;
            ch[1][i] = i<<1|1;
        }
        vc = 2*N;
    }
    Ptr find_ptr(Ptr v, Index x) {
        for (int i = L-1; i >= 0; i--) {
            v = ch[x>>i&1][v];
        }
        return v;
    }
    // pa[x]=p
    Ptr update(Ptr v, Index x, Index p) {
        for (int i = L-1; i >= 0; i--) {
            int b = x>>i&1;
            ch[b^1][vc] = ch[b^1][v];
            ch[b][vc] = vc+1; ++vc;
            v = ch[b][v];
        }
        pa[vc] = p;
        rk[vc] = rk[v];
        //!! any more info here.
        return vc++ - L;
    }
    // find root pa[v]=x, still return v not pa.
    Ptr find(Ptr _, Index x) {
        auto v = find_ptr(_,x);
        while (pa[v] != x) v = find_ptr(_,x = pa[v]);
        return v;
        //return pa[v] == x ? v : find(_,pa[v]);
    }
    Ptr join(Ptr _, Index x, Index y) {
        x = find(_,x);
        y = find(_,y);
        if (pa[x] == pa[y]) return _;
        if (rk[x] < rk[y]) swap(x,y);
        _ = update(_,pa[y],pa[x]); y = vc-1;
        // can possibly omit if no merge, save half-space
        // although ++rk[x] might affect past, but most cases no big deal.
        _ = update(_,pa[x],pa[x]); x = vc-1;
        if (rk[x] == rk[y]) ++rk[x];
        //!! merge here
        return _;
    }
    bool check(Ptr _, Index x, Index y) {
        x = find(_,x);
        y = find(_,y);
        return pa[x] == pa[y];
    }
};
// SNIPPETS_END

/*
 * https://www.luogu.com.cn/problem/P3402
void solve() {
    int n,m;
    cin >> n >> m;
    PersistentDsu d(n);
    vector<int> roots(m + 1);
    roots[0] = 1;
    for (int i = 1; i <= m; i++) {
        int op; cin >> op;
        if (op == 1) {
            int x,y;
            cin >> x >> y;
            --x;--y;
            roots[i] = d.join(roots[i-1],x,y);
        } else if (op == 2) {
            int v; cin >> v;
            roots[i] = roots[v];
        } else {
            int x,y;
            cin >> x >> y;
            --x;--y;
            roots[i] = roots[i-1];
            cout << (d.check(roots[i],x,y)?'1':'0') << '\n';
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}
*/
