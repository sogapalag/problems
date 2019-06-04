#include <bits/stdc++.h>

using namespace std;

const int N = 2e5+5; 

vector<int> g[N];
vector<int> p(N, -1); // parent
vector<int> d(N, -1); // depth
vector<bool> blc(N); // blocked.
int dx;

int q(char op, int u) {
    cout << op << ' ' << u << endl;
    int r; cin >> r;
    return r;
}

void pre(int u){
    for (int v: g[u]) {
        if (!~d[v]) {
            d[v] = d[u] + 1;
            p[v] = u;
            pre(v);
        }
    }
}

vector<int> sz(N);
int _n;

void comp_size(int u, int pa) {
    sz[u] = 1;
    for (int v: g[u]) {
        if (!blc[v] && v!=pa) {
            comp_size(v, u);
            sz[u] += sz[v];
        }
    }
}

int fcd(int u, int pa) {
    for (int v: g[u]) {
        if (!blc[v] && v!=pa && sz[v] > _n/2)
            return fcd(v, u);
    }
    return u;
}

int cd(int u) {
    comp_size(u, 0);
    _n = sz[u];
    return fcd(u, 0);
}

int qcd(int u) {
    int v = cd(u);
    int dis = q('d', v);
    if (!dis)
        return v;
    blc[v] = true;
    if (d[v] + dis == dx)
        return qcd(q('s', v));
    return qcd(p[v]);
}

// keep query centroid of subtree.
void solve() {
    int n; cin >> n;
    for (int i = 1; i < n; i++) {
        int x, y;
        cin >> x >> y;
        g[x].emplace_back(y);
        g[y].emplace_back(x);
    }
    dx = q('d', 1);
    d[1] = 0; pre(1);
    int res = qcd(1);
    cout << "! " << res;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
