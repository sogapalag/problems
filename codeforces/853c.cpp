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
ll c2(ll n){ return n*(n-1)/2; }
void solve() {
    int n,q;
    cin >> n >> q;
    vector<int> a(n+1);
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    vector<ll> res(q);
    vector<vector<tuple<int,int,int>>> evs(n+1), revs(n+1);
    for (int i = 0; i < q; i++) {
        int l,d,r,u;
        cin >> l >> d >> r >> u;
        // on 4 side
        res[i] += c2(l-1) + c2(d-1) + c2(n-r) + c2(n-u);
        evs[l].emplace_back(d,u, i);
        revs[r].emplace_back(d,u, i);
    }
    // linear sweep, exclude 4 dup. corner
    Fenwick<int> occur(n);
    for (int l = 1; l <= n; l++) {
        for (auto& _: evs[l]) {
            int d,u,i;
            tie(d,u,i) = _;
            res[i] -= c2(occur.query(d-1));
            res[i] -= c2(occur.query(u+1, n));
        }
        occur.add(a[l], 1);
    }
    fill(occur.v.begin(), occur.v.end(), 0);
    for (int r = n; r >= 1; r--) {
        for (auto& _: revs[r]) {
            int d,u,i;
            tie(d,u,i) = _;
            res[i] -= c2(occur.query(d-1));
            res[i] -= c2(occur.query(u+1, n));
        }
        occur.add(a[r], 1);
    }
    const ll tot = c2(n);
    for (auto& x: res) {
        cout << tot-x << '\n';
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}
