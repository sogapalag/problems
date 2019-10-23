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

// let B be bridge graph of original G
// then c=0 iff they in scc of B
void solve() {
    int n; ll m;
    cin >> n >> m;
    Dsu d(n);
    vector<pair<int, int>> cycle;
    int q; cin >> q;
    while (q--) {
        int x,y,c;
        cin >> x >> y >> c;
        if (c == 0) {
            d.join(x,y);
        } else {
            cycle.emplace_back(x,y);
        }
    }

    if (m == n-1) {
        cout << (cycle.empty()? "Yes" : "No");
        return;
    }
    for (auto& p: cycle) {
        int x,y;
        tie(x,y) = p;
        if (d.check(x,y)) {
            cout << "No"; return;
        }
    }
    set<int> s;
    for (int i = 0; i < n; i++) {
        s.insert(d.find(i));
    }
    ll k = s.size();
    ll lim = n + k*(k-3)/2;
    cout << (m<=lim ? "Yes" : "No");
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
