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

struct Edge {
    int u, v, cost;
    Edge() {}
    Edge(int _u, int _v, int _cost) : u(_u), v(_v), cost(_cost) {}
    bool operator<(const Edge& _oth) const {
        return cost<_oth.cost;
    }
};

// key idea, x/y separate consider
void solve() {
    int n; cin >> n;
    vector<pair<int, int>> a(n);
    for (auto& p: a) {
        cin >> p.first >> p.second;
    }
    sort(a.begin(), a.end());
    a.erase(unique(a.begin(), a.end()), a.end());
    n = a.size();
    vector<Edge> es;
    for (int i = 1; i < n; i++) {
        es.emplace_back(i-1, i, a[i].first-a[i-1].first);
    }
    vector<int> id(n);
    iota(id.begin(), id.end(), 0);
    sort(id.begin(), id.end(), [&](auto& u, auto& v){
        return a[u].second < a[v].second;
    });
    for (int i = 1; i < n; i++) {
        int i0 = id[i-1], i1 = id[i];
        es.emplace_back(i0,i1, a[i1].second - a[i0].second);
    }

    sort(es.begin(), es.end());
    Dsu d(n);
    long long res = 0;
    for (auto& e: es) {
        if (!d.check(e.u, e.v)) {
            d.join(e.u, e.v);
            res += e.cost;
        }
    }
    cout << res;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
