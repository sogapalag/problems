#include <bits/stdc++.h>

using namespace std;

template <typename T, typename U>
struct Seglazy {
    static const int H = 17; //20
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
            v[p].x = val;
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
    int x;
    
    Node() : x(-0x3f3f3f3f) {} // write your own identity
    Node(int _x) : x(_x) {}
    Node(const Node& _r) : x(_r.x) {}// write your own
    Node& operator = (const Node& _r) {
        x = _r.x; // write your own
        return *this;
    }
    Node& operator += (const Node& _r) {
        x = max(x, _r.x); // write your own  !! may not communitative
        return *this;
    }
    friend Node operator + (const Node& _lhs, const Node& _rhs) {
        return Node(_lhs) += _rhs; // derive from +=
    }
};

using Seg=Seglazy<Node, int>;

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

struct Task {
    int d, m; // deadline, minutes
    int i, k; // id, sorted id.
    Task() {}
    Task(int _d, int _m, int _i, int _k) : d(_d), m(_m), i(_i), k(_k) {}
};

// when new task put in consideration. 
// [] [in]  ->[]..[], right part delay each +m
// we can pre comp. their id[k] by deadline.
// then BIT for pref-sum calc delay. seglazy for make right delay +m
void solve() {
    int n; cin >> n;
    vector<Task> a(n+1);
    for (int i = 1; i <= n; i++) {
        int d, m;
        cin >> d >> m;
        a[i] = {d, m, i, 0};
    }
    sort(a.begin()+1, a.end(), [&](auto& u, auto& v){
            return u.d < v.d;
            });
    for (int k = 1; k <= n; k++) {
        a[k].k = k;
    }
    sort(a.begin()+1, a.end(), [&](auto& u, auto& v){
            return u.i < v.i;
            });
    Fenwick<int> sum(n);
    Seg delay;
    for (int i = 1; i <= n; i++) {
        sum.add(a[i].k, a[i].m);
        int delta = sum.query(a[i].k) - a[i].d;
        delay.assign(a[i].k, a[i].k+1, delta);
        delay.update(a[i].k+1, n+1, a[i].m);
        int res = delay.query(1, n+1).x;
        if (res < 0) res = 0;
        cout << res << "\n";
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
