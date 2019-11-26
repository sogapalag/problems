#include "../dinic.h"

struct BipartiteMaching {
    int n, m; // #l, #r
    int s, t;
    Dinic g;
    vector<int> right, left;
    BipartiteMaching(int _n, int _m) : n(_n), m(_m)
        , s(n+m)
        , t(n+m+1)
        , g(n+m+2, s, t)
        , right(n, -1)
        , left(m, -1)
    {
        for (int l = 0; l < n; l++) {
            g.add(s, l, 1);
        }
        for (int r = 0; r < m; r++) {
            g.add(n+r, t, 1);
        }
    }

    // l: [0..n),  r: [0..m)
    void add(int l, int r) {
        g.add(l, n+r, 1);
    }

    int match() {
        int res = g.flow();
        for (int r = 0; r < m; r++) {
            for (int i = g.pos[n+r]; i != -1; i = g.e[i].bro) {
                if (g.e[i].cap && g.e[i].v < n) {
                    right[left[r] = g.e[i].v] = r;
                    break;
                }
            }
        }
        return res;
    }
};
