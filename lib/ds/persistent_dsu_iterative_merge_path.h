#include <bits/stdc++.h>

using namespace std;

// DO NOT USE, even worse than non-merge in practice

// SNIPPETS_START persistent_dsu_iterative_merge_path
struct PersistentDsu {
    using Ptr = int;
    using Index = int;
    int n, L, N;
    vector<Ptr> lookup, trk;
    vector<Index> path;
    vector<Ptr> ch[2];
    vector<Index> pa;
    vector<int> rk;
    Ptr vc = 1;
    PersistentDsu(int _n) : n(_n) {
        L = 1; N = 2;
        while (N < n) ++L, N <<= 1;
        int S = 2*N + n*L*5;
        lookup.resize(2*N);
        trk.resize(2*N);
        path.reserve(L+10);
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
        lookup[1] = v;
        for (int i = L-1; i >= 0; i--) {
            v = ch[x>>i&1][v];
            lookup[(x+N)>>i] = v;
        }
        return v;
    }
    void mark(Index x, Index p) {
        trk[x+=N] = p+N; // !! p=0
        while (x >>= 1) trk[x] = 1;
    }
    // find root pa[v]=x, still return v not pa.
    Ptr find(Ptr _, Index x) {
        auto v = find_ptr(_,x);
        if (pa[v] == x) return v;
        while (pa[v] != x) {
            path.push_back(x);
            v = find_ptr(_,x = pa[v]);
        }
        path.pop_back();
        while (!path.empty()) {
            mark(path.back(), x); path.pop_back();
        }
        return v;
    }
    // for trk create one-to-one node.
    Ptr consume() {
        if (!trk[1]) return lookup[1];
        queue<int> q; q.push(1);
        while (!q.empty()) {
            auto u = q.front(); q.pop();
            if (u < N) {
                for (int i = 0; i < 2; i++) {
                    if (trk[u<<1|i]) q.push(u<<1|i);
                    else ch[i][vc] = ch[i][lookup[u]];
                }
            } else {
                pa[vc] = trk[u]-N; 
                rk[vc] = rk[lookup[u]];
                // any more info here
            }
            trk[u] = vc++;
        }
        auto ret = trk[1];
        // set ch with trk (new vc)
        q.push(1);
        while (!q.empty()) {
            auto u = q.front(); q.pop();
            if (u < N) {
                for (int i = 0; i < 2; i++) {
                    if (trk[u<<1|i]) {
                        ch[i][trk[u]] = trk[u<<1|i];
                        q.push(u<<1|i);
                    }
                }
            }
            trk[u] = 0;
        }
        return ret;
    }
    Ptr join(Ptr _, Index x, Index y) {
        x = find(_,x);
        y = find(_,y);
        if (pa[x] != pa[y]) {
            if (rk[x] < rk[y]) swap(x,y);
            mark(pa[y], pa[x]);
            //mark(pa[x], pa[x]);
        }
        auto v = consume();
        if (pa[x] != pa[y]) {
            x = find_ptr(v, pa[x]);
            y = find_ptr(v, pa[y]);
            if (rk[x] == rk[y]) ++rk[x];
            // merge here
        }
        return v;
    }
    Ptr check(Ptr _, Index x, Index y) {
        x = find(_,x);
        y = find(_,y);
        auto v = consume();
        if (pa[x] != pa[y]) v *= -1;
        return v;
    }
};
// SNIPPETS_END
