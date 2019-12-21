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
// .. |l.. |r..
// treat all >k as #
// it's optimal let # <=r move to left-most, # >=l move to right-most
void solve() {
    int n; cin >> n;
    vector<int> a(n+1), pos(n+1);
    for (int i = 1; i <= n; i++) {
        cin >> a[i]; pos[a[i]] = i;
    }
    Fenwick<int> f(n), g(n);
    for (int i = 1; i <= n; i++) {
        g.add(i, 1);
    }

    int l,r;
    l = r = pos[1];
    vector<ll> res(n+1); res[1] = 0; // fk... why not just print, vector<int>
    g.add(l, -1); f.add(l, 1);
    ll base = 0;
    ll oth = 0;
    for (int i = 2; i <= n; i++) {
        int p = pos[i];
        base += f.query(p, n);
        g.add(p, -1);
        
        if (p < l) {
            oth -= f.query(p);
            oth += g.query(p, l);
        } else if (p > r) {
            oth -= f.query(p, n);
            oth += g.query(r, p);
        } else {
            oth -= f.query(p);
        }
        f.add(p, 1); 

        l = bs_first<int>(1, n+1, [&](int x){
                return f.query(x) >= (i+1)/2;
                });
        if (i&1) r = l;
        else {
            r = bs_first<int>(1, n+1, [&](int x){
                    return f.query(x) >= i/2 + 1;
                    });
        }
        res[i] = base + oth;
    }
    for (int i = 1; i <= n; i++) {
        cout << res[i] << ' ';
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
