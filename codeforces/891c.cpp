#include <bits/stdc++.h>

using namespace std;
using pi=pair<int, int>;

struct Dsu {
    int n;
    vector<int> p;
    vector<int> r;
    vector<pi> histo;

    Dsu(int _n) { n = _n; p.resize(n); r.resize(n); init(); }
    inline void init() {
        for (int i = 0; i < n; i++) {
            p[i] = i;
            r[i] = 1;
        }
    }
    inline int find(int x) { // don't compress path
        while (x != p[x]) x = p[x];
        return x;
        //return p[x] == x ? x: p[x] = find(p[x]);
    }
    inline int join(int x, int y) {
        x = find(x); y = find(y);
        if (x == y) return 0;
        if (r[x] < r[y]) swap(x, y);
        histo.emplace_back(x, y);
        p[y] = x; r[x] += r[y];
        return 1;
    }
    inline int join(pi e) {
        return join(e.first, e.second);
    }
    void roll_back() {
        int x,y;
        tie(x,y) = histo.back(); histo.pop_back();
        r[x] -= r[y]; p[y] = y;
    }
    inline bool check(int x, int y) {
        return find(x) == find(y);
    }
    inline bool check(pi e) {
        return check(e.first, e.second);
    }
};
const int N = 5e5+10; 
void solve() {
    int n,m;
    cin >> n >> m;
    vector<int> u(m), v(m), w(m);
    vector<vector<int>> ws(N);
    for (int i = 0; i < m; i++) {
        cin >> u[i] >> v[i] >> w[i]; 
        --u[i]; --v[i];
        ws[w[i]].push_back(i);
    }

    vector<vector<vector<int>>> qrs(N);
    int q; cin >> q;
    for (int i = 0; i < q; i++) {
        int k; cin >> k;
        vector<int> id(k);
        for (auto& x: id) {
            cin >> x; x--;
        }
        sort(id.begin(), id.end(), [&](auto& u, auto& v){
            return w[u] < w[v];
        });
        while (!id.empty()) {
            int wei = w[id.back()];
            qrs[wei].emplace_back();
            auto& a = qrs[wei].back();
            while (!id.empty() && w[id.back()] == wei) {
                a.push_back(id.back()); id.pop_back();
            }
            a.push_back(i);
        }
    }

    Dsu d(n);
    vector<bool> res(q, true);
    for (int x = 1; x < N; x++) {
        // indep consider each a
        for (auto& a: qrs[x]) {
            int i = a.back(); a.pop_back();
            int cnt = 0;
            for (int k: a) {
                int z = d.join(u[k], v[k]);
                if (!z) {
                    res[i] = false; break;
                }
                cnt += z;
            }
            // roll back
            while (cnt--) {
                d.roll_back();
            }
        }
        // kruskal
        for (int k: ws[x]) {
            d.join(u[k], v[k]);
        }
    }
    for (int i = 0; i < q; i++) {
        cout << (res[i] ? "YES\n" : "NO\n");
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}
