#include <bits/stdc++.h>

using namespace std;

struct Dsu {
    int n;
    vector<int> p;
    vector<int> r;
    
    Dsu(int _n) { n = _n; p.resize(n); r.resize(n); init(); }
    inline void init() {
        for (int i = 0; i < n; i++) {
            p[i] = i;
            r[i] = 1;
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
        return true;
    }
    inline bool check(int x, int y) {
        return find(x) == find(y);
    }
};

void solve() {
    int n,m;
    cin >> n >> m;
    vector<array<int,3>> e(n-1);
    for (int i = 0; i < n-1; i++) {
        int x,y,z;
        cin >> x >> y >> z;
        x--;y--;
        e[i]={x,y,z};
    }
    sort(e.begin(), e.end(), [&](auto& u, auto& v){
        return u[2] < v[2];
    });
    Dsu d(n);
    vector<pair<int, int>> q(m);
    for (int i = 0; i < m; i++) {
        int x; cin >> x;
        q[i] = {x,i};
    }
    sort(q.begin(), q.end());
    int j = 0;
    vector<long long> res(m);
    long long sum = 0;
    for (int i = 0; i < m; i++) {
        while (j<n-1 && e[j][2] <= q[i].first) {
            int u = d.find(e[j][0]), v = d.find(e[j][1]);
            sum += 1ll*d.r[u]*d.r[v];
            d.join(u,v);
            j++;
        }
        res[q[i].second] = sum;
    }
    for (auto& x: res) {
        cout << x << ' ';
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
