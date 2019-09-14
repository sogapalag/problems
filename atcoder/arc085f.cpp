#include <bits/stdc++.h>

using namespace std;

template <typename T, typename U>
struct Seglazy {
    static const int H = 19; //20
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
    int x;
    
    Node() : x(0x3f3f3f3f) {} // write your own identity
    Node(int _x) : x(_x) {}
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

using Seg=Seglazy<Node, int>;

// treat seg[r] as min cost when some 1s used expand to r. i.e. a[r]=1, a[>r] = 0
// editorial has a transformed version, consider equiv: min (0,1)-(0,0). omit
// for easy understand, keep in mind, we care when right-most 1 is r, its cost
// then by b[i]=1/0, we can dertermin whether [0,i) +1 or [i,n] +1
void solve() {
    int n; cin >> n;
    vector<int> b(n+1);
    for (int i = 1; i <= n; i++) {
        cin >> b[i];
    }
    int q; cin >> q;
    vector<vector<int>> g(n+1);
    while (q--) {
        int x,y;
        cin >> x >> y;
        g[x].emplace_back(y);
    }
    for (int i = 1; i <= n; i++) {
        sort(g[i].begin(), g[i].end());
    }

    Seg s;
    s.assign(0,1, 0);
    for (int i = 1; i <= n; i++) {
        for (int r: g[i]) {
            s.assign(r, r+1, s.query(0, r).x);
        }
        // for [0,i) since no 1 expand to i, (0,1), their cost +1
        if (b[i]) s.update(0, i, 1);
        // for [i,.. since they expand beyond, and since we operate by i inc. order, so (1,0) for sure
        // their cost +1
        else s.update(i, n+1, 1);
    }
    cout << s.query(0, n+1).x;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
