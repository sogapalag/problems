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

using ll=long long ;
// this problem may got some difficulty to understand.
// conclusion optim form, is that for some root with max a-b (>=0), visit(pay) some sub-components Gs, then root, then some final G
// keep in mind a simple fact. if cash = max(a-b) + sum(b). then we have a 'path' end with u*=argmax(a-b)
// use this fact, it should be easy to understand.
// and easy to imagine cash >= sum, so into G, obviously we can select any init node we want.
void solve() {
    int n,m;
    cin >> n >> m;
    vector<int> a(n), b(n);
    vector<vector<int>> g(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i] >> b[i];
    }
    for (int _ = 0; _ < m; _++) {
        int x,y;
        cin >> x >> y;
        x--;y--;
        g[x].emplace_back(y);
        g[y].emplace_back(x);
    }
    vector<int> id(n);
    iota(id.begin(), id.end(), 0);
    sort(id.begin(), id.end(), [&](int i, int j){
            return a[i]-b[i] < a[j]-b[j];
            });
    Dsu d(n);
    vector<ll> base(n);
    vector<ll> need(n);
    for (int i = 0; i < n; i++) {
        base[i] = b[i];
        need[i] = max(a[i], b[i]);
    }
    vector<bool> trk(n, false);
    // bottem-up
    for (int u: id) {
        trk[u] = true;
        set<int> s;
        for (int v: g[u]) {
            if (trk[v]) {
                s.insert(d.find(v));
            }
        }
        if (s.empty()) continue;
        for (int v: s) {
            base[u] += base[v];
            d.join(u, v); // an idiom way, p(u)=u alises to base summation
        }
        ll leaving_need = max(a[u]-b[u], 0);//without 0 is fine, since need[v]>=0, but idiom 
        ll optim = 1e18;
        for (int v: s) {
            ll leaving = max(need[v], leaving_need);
            ll before = base[u] - base[v];
            optim = min(optim, leaving + before);
        }
        need[u] = optim;
    }
    ll res = need[d.find(0)];
    cout << res;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
