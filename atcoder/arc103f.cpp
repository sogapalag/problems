#include <bits/stdc++.h>

using namespace std;
using ll = long long ;
struct Node {
    int i;
    ll d;
    Node() {}
    Node(int _i, ll _d) : i(_i), d(_d) {}
    bool operator<(const Node& _r) const {
        return d > _r.d;
    }
};

// by decresing d, find its pa
void solve() {
    int n; cin >> n;
    vector<int> p(n,-1), sz(n,1);
    set<Node> s;
    for (int i = 0; i < n; i++) {
        ll d; cin >> d;
        s.insert({i,d});
    }
    vector<vector<int>> g(n);
    vector<pair<int, int>> e;
    while ((int)s.size()>1) {
        auto it = s.begin();
        auto v = *it; s.erase(it);
        ll target = v.d + 2*sz[v.i] - n; 
        auto jt = s.lower_bound({-1, target});
        if (jt == s.end() || jt->d != target) {
            cout << -1; return;
        }
        p[v.i] = jt->i;
        sz[jt->i] += sz[v.i];
        g[jt->i].emplace_back(v.i);
        e.emplace_back(jt->i, v.i);
    }
    int root = -1;
    for (int i = 0; i < n; i++) {
        if (p[i] == -1) root = i;
    }
    function<ll(int)> dfs = [&](int u){
        ll sum = sz[u]-1;
        for (int v: g[u])
            sum += dfs(v);
        return sum;
    };
    auto it = s.begin();
    if (sz[root] != n || it->d != dfs(root)) {
        cout << -1; return;
    }
    for (auto& p: e) {
        cout << p.first+1 << ' ' << p.second+1 << "\n";
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
