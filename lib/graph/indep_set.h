#include "bip_match.h"

// SNIPPETS_START graph_bip_indep_set
// true, means in IndepSet
// otherwise, in VertexCover
struct IndepSet : Bip {
    vector<bool> L,R;

    IndepSet(int _n) : Bip(_n), L(n, false), R(m, true) {}
    IndepSet(int _n, int _m) : Bip(_n,_m), L(n, false), R(m, true) {}

    void dfs_set(int l) {
        L[l] = true;
        for (int r: g[l]) {
            if (left[r] != -1 && !L[left[r]]) {
                R[r] = false;
                dfs_set(left[r]);
            }
        }
    }

    int get_indep_set() {
        int vertex_cover = match();
        vector<int> right(n, -1);
        for (int r = 0; r < m; r++) {
            if (left[r] != -1) {
                right[left[r]] = r;
            }
        }
        for (int l = 0; l < n; l++) {
            if (right[l] == -1 && !L[l]) {
                dfs_set(l);
            }
        }
        int indep_set = 0;
        for (bool l: L) indep_set += l;
        for (bool r: R) indep_set += r;
        assert(indep_set + vertex_cover == n + m);
        return indep_set;
    }
};
// SNIPPETS_END
