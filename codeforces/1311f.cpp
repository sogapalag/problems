#include <bits/stdc++.h>

using namespace std;
using ll=long long;
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
// for x0 < x1, d = x1-x0, don't collide iff v0 < v1
void solve() {
    int n; cin >> n;
    vector<pair<int, int>> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i].first;
    }
    vector<int> Vs;
    for (int i = 0; i < n; i++) {
        cin >> a[i].second;
        Vs.push_back(a[i].second);
    }
    sort(a.begin(), a.end());
    sort(Vs.begin(), Vs.end());
    Vs.erase(unique(Vs.begin(), Vs.end()), Vs.end());
    ll res = 0;
    Fenwick<ll> s(Vs.size()), c(Vs.size());
    for (int i = 0; i < n; i++) {
        int x,v;
        tie(x,v) = a[i];
        v = lower_bound(Vs.begin(), Vs.end(), v) - Vs.begin();
        v++;
        res += c.query(v) * x - s.query(v);
        c.add(v, 1);
        s.add(v, x);
    }

    cout << res;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}
