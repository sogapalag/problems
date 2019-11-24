#include <bits/stdc++.h>

using namespace std;

// SNIPPETS_START grid
struct Grid {
    using T = int;
    //using T = long long;
    using G = vector<vector<T>>;
    int n, m;
    G g;
    Grid(int _n, int _m) : n(_n), m(_m) {
        g.resize(n+2);
        for (auto& r: g) {
            r.assign(m+2, 0);
        }
    }
    Grid(const G& _g) : n(_g.size()), m(_g[0].size()) {
        g.resize(n+2);
        for (auto& r: g) {
            r.assign(m+2, 0);
        }
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                g[i+1][j+1] = _g[i][j];
            }
        }
    }

    // add diff/delta, after finish add, call build_sum get a[i][j], call again can get sum[i][j]
    // 1-based [l..r)
    // add rect-area each cell val
    void add_rect(int il, int jl, int ir, int jr, T val) {
        g[il][jl] += val;
        g[il][jr] -= val;
        g[ir][jl] -= val;
        g[ir][jr] += val;
    }

    void build_sum() {
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= m; j++) {
                g[i][j] += g[i][j-1] - g[i-1][j-1] + g[i-1][j];
            }
        }
    }
    // 0-based [l..r)
    inline T query_sum(int il, int jl, int ir, int jr) {
        return (g[ir][jr] - g[il][jr]) - (g[ir][jl] - g[il][jl]);
    }
};
// SNIPPETS_END
