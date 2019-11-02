#include <bits/stdc++.h>

using namespace std;
using ll=long long;
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
    int x, y; ll cost;
    Edge() {}
    Edge(int _x, int _y, ll _cost) : x(_x), y(_y), cost(_cost) {}
    bool operator<(const Edge& _oth) const {
        return cost < _oth.cost;
    }
};


// let n = dummy node electricity, build c[i], means connect(i,n)
// then find MST, note min c[i] always connect to n, and ensure.
void solve() {
    int n; cin >> n;
    vector<int> x(n),y(n),c(n),k(n);
    for (int i = 0; i < n; i++) {
        cin >> x[i] >> y[i];
    }
    int mic = 1e9+100, id = -1;
    for (int i = 0; i < n; i++) {
        cin >> c[i];
        if (c[i] < mic) {
            mic = c[i];
            id = i;
        }
    }
    for (int i = 0; i < n; i++) {
        cin >> k[i];
    }
    ll tot = 0;
    vector<int> cen; cen.reserve(n);
    Dsu d(n+1);
    d.join(id, n); cen.emplace_back(id); tot += c[id];
    vector<Edge> es; es.reserve(n*n);
    for (int i = 0; i < n; i++) {
        if (i!=id) {
            es.emplace_back(i, n, c[i]);
        }
    }
    for (int i = 0; i < n; i++) {
        for (int j = i+1; j < n; j++) {
            ll dis = abs(x[i]-x[j]) + abs(y[i]-y[j]);
            es.emplace_back(i, j, (k[i]+k[j]) * dis);
        }
    }
    sort(es.begin(), es.end());
    vector<pair<int, int>> res; res.reserve(n*n);
    for (auto& e: es) {
        if (!d.check(e.x, e.y)) {
            d.join(e.x, e.y); tot += e.cost;
            if (e.y == n) {
                cen.emplace_back(e.x);
            } else {
                res.emplace_back(e.x, e.y);
            }
        }
    }
    cout << tot << "\n";
    cout << cen.size() << "\n";
    for (auto& x: cen) {
        cout << (x+1) << ' ';
    }cout << "\n";
    cout << res.size() << "\n";
    for (auto& p: res) {
        cout << (p.first+1) << ' ' << (p.second+1) << "\n";
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
