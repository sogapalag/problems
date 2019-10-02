#include <bits/stdc++.h>

using namespace std;

template <typename T, typename U>
struct Seglazy {
    static const int H = 18; //20
    static const int SZ = 1<<H;
    int sz_v;
    const T ID;  // identity
    const U UN;  // not info
    vector<T> v; // tree
    vector<U> d; // lazy
    
    Seglazy() : sz_v(SZ<<1), ID(0), UN(0), v(sz_v, 0), d(sz_v, 0) {
        //v.resize(sz_v);
        //d.resize(sz_v);
    }
    inline int len(int p) {
        return 1 << (H + __builtin_clz(p) - 31);
    }
    void build(int p=1, int l=0, int r=SZ) {
        if (l + 1 == r) {
            //set leaf
            return;
        }
        assert(l != r);
        int m = (l+r)>>1, pl = p<<1, pr = p<<1|1;
        build(pl, l, m);
        build(pr, m, r);
        v[p] = v[pl] + v[pr];
    }
    inline void apply(int p) {// do!! use info, may need length, pass l, r in
        v[p] += d[p] * len(p);
    }
    inline void store(int p, const U& val) {// do!! store info, careful!! info chain
        d[p] += val;
    }
    inline void push(int p) {
        apply(p);
        if (p <= SZ) {
            store(p<<1, d[p]);
            store(p<<1|1, d[p]);
        }
        d[p] = UN;
    }
    void update(int _l, int _r, const U& val, int p=1, int l=0, int r=SZ) {
        if (d[p] != UN) push(p);
        if (_r <= l || r <= _l) return;
        if (_l <= l && r <= _r) { // update by info
            store(p, val);
            push(p);
            return;
        }
        int m = (l+r)>>1, pl = p<<1, pr = p<<1|1;
        update(_l, _r, val, pl, l, m);
        update(_l, _r, val, pr, m, r);
        v[p] = v[pl] + v[pr];
    }
    T query(int _l, int _r, int p=1, int l=0, int r=SZ) {
        if (d[p] != UN) push(p);
        if (_r <= l || r <= _l) { return ID; }
        if (_l <= l && r <= _r) { return v[p]; }
        int m = (l+r)>>1, pl = p<<1, pr = p<<1|1;
        return query(_l, _r, pl, l, m) + query(_l, _r, pr, m, r);
    }    
};

typedef Seglazy<long long, long long> Seg;

void solve() {
    int n,m;
    cin >> n >> m;
    vector<int> a(m);
    for (auto& x: a) {
        cin >> x;
    }
    Seg s;
    for (int i = 1; i < m; i++) {
        int x = a[i-1], y = a[i];
        if (x > y) swap(x,y);
        if (x == y) continue;
        // seglazy is overkill, diff on BIT is fine
        s.update(1, x, y-x);
        s.update(x, x+1, y-1);
        s.update(x+1, y, y-x-1);
        s.update(y,y+1, x);
        s.update(y+1, n+1, y-x);
    }
    for (int i = 1; i <= n; i++) {
        cout << s.query(i, i+1) << ' ';
    }
}
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
void solve2() {
    int n,m;
    cin >> n >> m;
    vector<int> a(m);
    for (auto& x: a) {
        cin >> x;
    }
    ll base = 0;
    Fenwick<ll> f(n);
    for (int i = 1; i < m; i++) {
        int x = a[i-1], y = a[i];
        if (x > y) swap(x,y);
        if (x == y) continue;
        base += y-x;
        // BIT is also overkill, normal presum is fine, since query[1..n]
        f.add(x, x-1);
        f.add(x+1, -x);
        f.add(y, 2*x-y+1);
        f.add(y+1, y-2*x);
    }
    for (int i = 1; i <= n; i++) {
        ll res = base + f.query(i);
        cout << res << ' ';
    }
}

void solve3() {
    int n,m;
    cin >> n >> m;
    vector<int> a(m);
    for (auto& x: a) {
        cin >> x;
    }
    ll base = 0;
    vector<ll> diff(n+3, 0);
    for (int i = 1; i < m; i++) {
        int x = a[i-1], y = a[i];
        if (x > y) swap(x,y);
        if (x == y) continue;
        base += y-x;
        diff[x] += x-1;
        diff[x+1] += -x;
        diff[y] += 2*x-y+1;
        diff[y+1] += y-2*x;
    }
    ll res = base;
    for (int i = 1; i <= n; i++) {
        res += diff[i];
        cout << res << ' ';
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve3();
    cout << endl;
}
