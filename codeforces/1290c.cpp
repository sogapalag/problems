#include <bits/stdc++.h>

using namespace std;

struct Dsu {
    int n;
    vector<int> p;
    vector<int> r, du;
    vector<bool> must;
    
    Dsu(int _n) { n = _n; p.resize(n); r.resize(n); must.assign(n, 0);
        du.resize(n);
        init(); }
    inline void init() {
        for (int i = 0; i < n; i++) {
            p[i] = i;
            r[i] = 1;
            if(i&1) du[i] = 1;
        }
    }
    inline int find(int x) {
        return p[x] == x ? x: p[x] = find(p[x]);
    }
    inline bool join(int x, int y) {
        x = find(x); y = find(y);
        if (x == y) return false;
        if (r[x] < r[y]) swap(x, y);
        p[y] = x; r[x] += r[y];
        du[x] += du[y];
        must[x] = must[x] || must[y];
        return true;
    }
    inline bool check(int x, int y) {
        return find(x) == find(y);
    }
    // return using which part
    int used(int x) {
        int l = find(x);
        int r = find(x^1);
        assert(l != r);
        assert(must[l] + must[r] < 2);
        if (must[l]) return du[l];
        if (must[r]) return du[r];
        return min(du[l], du[r]);
    }
    void set(int x) {
        must[find(x)] = true;
    }
};

// let [k].[0/1] be choose or not A_i
// no matter same/diff edge, each scc, must exsit 2-coloring/partition. by the problem ensured.
// i,i^1 won't be in same scc.
// each update, get best of which.
void solve() {
    int n,k;
    cin >> n >> k;
    string s; cin >> s;
    vector<vector<int>> g(n);
    for (int i = 0; i < k; i++) {
        int m; cin >> m;
        for (int _ = 0; _ < m; _++) {
            int x; cin >> x;
            x--;
            g[x].push_back(i);
        }
    }
    Dsu d(2*k);
int res = 0;
    for (int i = 0; i < n; i++) {
        int bit = s[i]-'0';
        bit ^= 1;
        auto& a = g[i];
        sort(a.begin(), a.end());
        a.erase(unique(a.begin(), a.end()), a.end());
        if (a.size() == 1) {
            int x = a[0]<<1;
            res -= d.used(x^bit);
            d.set(x^bit);
            res += d.used(x^bit);
        } else if (a.size() == 2) {
            int x = a[0]<<1, y = a[1]<<1;
            if (d.check(x, y^bit)) {}
            else {
                res -= d.used(x);
                res -= d.used(y^bit);
                d.join(x, y^bit);
                d.join(x|1, (y|1)^bit);
                res += d.used(x);
            }
        }
        cout << res << "\n";
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}
