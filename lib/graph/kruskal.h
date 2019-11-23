#include <bits/stdc++.h>

using namespace std;

struct Dsu {
    int n;
    vector<int> p;
    
    Dsu(int _n) { n = _n; p.resize(n); init(); }
    inline void init() {
        for (int i = 0; i < n; i++) {
            p[i] = i;
        }
    }
    inline int find(int x) {
        return p[x] == x ? x: p[x] = find(p[x]);
    }
    inline bool join(int x, int y) {
        x = find(x); y = find(y);
        if (x == y) return false;
        p[y] = x; return true;
    }
    inline bool check(int x, int y) {
        return find(x) == find(y);
    }
};

// SNIPPETS_START graph_kruskal
struct Kruskal {
    using CT = int;
    //using CT = long long;
    struct Edge {
        int u, v;
        CT cost;
        Edge() {}
        Edge(int _u, int _v, CT _cost) : u(_u), v(_v), cost(_cost) {}
        bool operator<(const Edge& _oth) const {
            return cost < _oth.cost;
        }
    };

    int n;
    vector<Edge> es;

    Kruskal(int _n) : n(_n)
        {
        es.reserve(n*2);
    }
    inline void add(int u, int v, CT cost) {
        es.emplace_back(u, v, cost);
    }
    inline void add(const Edge& e) {
        es.push_back(e);
    }
    inline void add(const vector<Edge>& _es) {
        for (auto& e: es) {
            es.push_back(e);
        }
    }

    tuple<CT, vector<Edge>> get_mst() {
        CT tot = 0;
        sort(es.begin(), es.end());
        Dsu d(n);
        vector<Edge> mst; mst.reserve(n);
        for (auto& e: es) {
            if (d.join(e.u, e.v)) {
                tot += e.cost;
                mst.push_back(e);
            }
        }
        return {tot, mst};
    }
};
// SNIPPETS_END
