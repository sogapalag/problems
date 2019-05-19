#include <bits/stdc++.h>

using namespace std;


template <typename T, typename U>
struct Seglazy {
    static const int H = 17;
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
       // store(p<<1, d[p]);
       // store(p<<1|1, d[p]);
       // apply(p<<1); //TODO, repeated info
       // apply(p<<1|1);
        d[p<<1] += d[p];
        d[p<<1|1] += d[p];
        v[p<<1] += d[p] * len(p<<1);
        v[p<<1|1] += d[p] * len(p<<1|1);
        d[p] = UN;
    }
    void update(int _l, int _r, const U& val, int p=1, int l=0, int r=SZ) {
        if (_r <= l || r <= _l) return;
        if (_l <= l && r <= _r) { // update by info
           // store(p, val);
           // apply(p); // TODO
            d[p] += val;
            v[p] += val * len(p);
            return;
        }
        if (d[p] != UN) {
            push(p);
        }
        int m = (l+r)>>1, pl = p<<1, pr = p<<1|1;
        update(_l, _r, val, pl, l, m);
        update(_l, _r, val, pr, m, r);
        v[p] = v[pl] + v[pr];
    }
    T query(int _l, int _r, int p=1, int l=0, int r=SZ) {
        if (_r <= l || r <= _l) { return ID; }
        if (_l <= l && r <= _r) { return v[p]; }
        if (d[p] != UN) {
            push(p);
        }
        int m = (l+r)>>1, pl = p<<1, pr = p<<1|1;
        return query(_l, _r, pl, l, m) + query(_l, _r, pr, m, r);
    }    
};

typedef Seglazy<long long, long long> Seg;
void solve() {
    int n, c;
    cin >> n >> c;
    Seg seg;
    while (c--) {
        int op, x, y, val;
        cin >> op >> x >> y;
        if (op) {
            cout << seg.query(x, y+1) << "\n";
        } else {
            cin >> val;
            seg.update(x, y+1, val);
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int t; cin >> t;
    while (t--) {
        solve();
    }
    cout << endl;
}
