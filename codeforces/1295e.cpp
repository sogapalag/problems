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


template <typename T, typename U>
struct Seglazy {
    static const int H = 18; //20
    static const int SZ = 1<<H;
    int sz_v;
    const T ID;  // identity
    const U UN;  // not info
    vector<T> v; // tree
    vector<U> d; // lazy
    
    Seglazy() : sz_v(SZ<<1), ID(), UN(0), v(sz_v), d(sz_v, 0) {
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
        v[p].x += d[p]; //.x
    }
    inline void store(int p, const U& val) {// do!! store info, careful!! info chain
        d[p] += val;
    }
    inline void push(int p) {
        apply(p);
        if (p < SZ) {
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
    // 1-elem
    void assign(int _l, int _r, const U& val, int p=1, int l=0, int r=SZ) {
        if (d[p] != UN) push(p);
        if (_r <= l || r <= _l) return;
        if (_l <= l && r <= _r) { // update by info
            assert(_l+1 == _r);
            v[p].x = min(v[p].x, val); // not assign, mini
            return;
        }
        int m = (l+r)>>1, pl = p<<1, pr = p<<1|1;
        assign(_l, _r, val, pl, l, m);
        assign(_l, _r, val, pr, m, r);
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

struct Node {// monoid
    ll x;
    
    Node() : x(0x3f3f3f3f3f3f3f3f) {} // write your own identity
    Node(ll _x) : x(_x) {}
    Node(const Node& _r) : x(_r.x) {}// write your own
    Node& operator = (const Node& _r) {
        x = _r.x; // write your own
        return *this;
    }
    Node& operator += (const Node& _r) {
        x = min(x, _r.x); // write your own  !! may not communitative
        return *this;
    }
    friend Node operator + (const Node& _lhs, const Node& _rhs) {
        return Node(_lhs) += _rhs; // derive from +=
    }
};

using Seg=Seglazy<Node, ll>;


void solve() {
    int n; cin >> n;
    vector<int> p(n+1), pos(n+1), a(n+1);
    for (int i = 1; i <= n; i++) {
        cin >> p[i]; pos[p[i]] = i;
    }
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    ll res = min(a[1], a[n]);
    // WA k not necessary be cut i.
    //Fenwick<> f(n);
    //ll sum = 0;
    //for (int k = 1; k < n; k++) {
    //    if (f.query(k, k)) sum -= a[pos[k]];
    //    else sum += a[pos[k]];
    //    f.add(p[k], 1);
    //    if (p[k] <= k) sum -= a[k];
    //    else sum += a[k];
    //    res = min(res, sum);
    //}
    //cout << res;
    
    Seg seg;
    ll sum = 0;
    for (int i = 1; i <= n; i++) {
        sum += a[pos[i]];
        seg.assign(i,i+1, sum);
    }

    for (int k = 1; k < n; k++) {
        int x = p[k], c = a[k];
        seg.update(1, x, c); // have to move right
        seg.update(x, n+1, -c); // no more need to move left
        auto tmp = seg.query(1, n+1).x;
        cerr<<tmp<<endl;
        res = min(res, tmp);
    }
    cout << res;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}
