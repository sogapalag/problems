#include <bits/stdc++.h>

using namespace std;

template <typename T=int>
struct Fenwick {
    int n;
    vector<T> v;
    
    Fenwick(int size = 100005) : n(size), v(n+1, 0) {}
    inline void add(int p, T val) {
        for (; p <= n; p += (p&-p)) { v[p] += val; }
    }
    inline T query(int p) {
        T tmp = 0;
        for (; p > 0; p -= (p&-p)) { tmp += v[p]; }
        return tmp;
    }
    inline T query(int l, int r) {
        return query(r) - query(l-1);
    }
};
using ll=long long;

void solve() {
    int n,q;
    cin >> n >> q;
    vector<int> a(n+1), pos(n+1);
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        pos[a[i]] = i;
    }
    vector<vector<int>> evs(n+1);
    for (int d = 1; d <= n; d++) {
        for (int x = d; x <= n; x+=d) {
            int p0 = pos[d];
            int p1 = pos[x];
            if (p0 > p1) swap(p0, p1);
            evs[p0].push_back(p1);// a pair of relation
        }
    }
    
    vector<vector<pair<int,int>>> qrs(n+1);
    for (int i = 0; i < q; i++) {
        int l,r;
        cin >> l >> r;
        qrs[l].emplace_back(r, i);
    }

    Fenwick<int> f(n); // at most nlogn, no need ll
    vector<int> res(q);
    for (int l = n; l >= 1; l--) {
        for (int r: evs[l]) {
            f.add(r, 1);
        }
        for (auto& _: qrs[l]) {
            int r,i;
            tie(r,i) = _;
            res[i] = f.query(r); // as long as r' <= r, 
        }
    }
    for (auto& x: res) {
        cout << x << "\n";
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}
