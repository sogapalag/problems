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
// when range [l, r), has property notP~P, want first P.
// when return r, means not found.
template <typename T>
T bs_first(T l, T r, function<bool (T)> f) {
    assert(l < r);
    T mid;
    while (l != r) {
        mid = l + (r-l)/2;
        if (f(mid)) {
            r = mid;
        }else {
            l = mid + 1;
        }
    }
    return r;
}
// we need know x's left two closest greater, and right two closest greater' pos.
// set also works
void solve() {
    int n; cin >> n;
    vector<int> a(n+1);
    vector<int> pos(n+1);
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        pos[a[i]] = i;
    }
    Fenwick<int> f(n);
    long long res = 0;
    for (int i = n; i >= 1; i--) {
        int k = pos[i];
        int lef = f.query(k);
        int l1=0, l0=0;
        if (lef > 0) l0 = bs_first<int>(1, k, [&](int x){return f.query(x)>=lef;});
        if (lef > 1) l1 = bs_first<int>(1, k, [&](int x){return f.query(x)>=lef-1;});
        int r0=n+1, r1=n+1;
        int rig = f.query(k, n);
        if (rig > 0) r0 = bs_first<int>(k,n+1, [&](int x){return f.query(k, x)>=1;});
        if (rig > 1) r1 = bs_first<int>(k,n+1, [&](int x){return f.query(k, x)>=2;});
        res += 1ll*(l0-l1)*(r0-k)*i;
        res += 1ll*(r1-r0)*(k-l0)*i;
        f.add(k, 1);
    }
    cout << res;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
