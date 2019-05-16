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
        if (r[x] < r[y])
            swap(x, y);
        p[y] = x; 
        r[x] += r[y];
        return true;
    }
    inline bool check(int x, int y) {
        return find(x) == find(y);
    }
};

void solve() {
    int n, m;
    cin >> n >> m;
    Dsu dsu(n);
    while (m--) {
        int k; cin >> k;
        vector<int> a(k);
        for (auto& x: a) {
            cin >> x;
            x--;
        }
        for (int i = 1; i < k; i++) {
            dsu.join(a[i-1], a[i]);
        }
    }
    for (int i = 0; i < n; i++) {
        int x = dsu.find(i);
        cout << dsu.r[x] << ' ';
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
