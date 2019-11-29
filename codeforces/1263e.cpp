#include <bits/stdc++.h>

using namespace std;

template <typename T, typename U>
struct Seglazy {
    static const int H = 20;
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
        v[p].y += d[p];
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
    //// 1-elem
    //void assign(int _l, int _r, const U& val, int p=1, int l=0, int r=SZ) {
    //    if (d[p] != UN) push(p);
    //    if (_r <= l || r <= _l) return;
    //    if (_l <= l && r <= _r) { // update by info
    //        assert(_l+1 == _r);
    //        v[p].x = min(v[p].x, val); // not assign, mini
    //        return;
    //    }
    //    int m = (l+r)>>1, pl = p<<1, pr = p<<1|1;
    //    assign(_l, _r, val, pl, l, m);
    //    assign(_l, _r, val, pr, m, r);
    //    v[p] = v[pl] + v[pr];

    //}
    T query(int _l, int _r, int p=1, int l=0, int r=SZ) {
        if (d[p] != UN) push(p);
        if (_r <= l || r <= _l) { return ID; }
        if (_l <= l && r <= _r) { return v[p]; }
        int m = (l+r)>>1, pl = p<<1, pr = p<<1|1;
        return query(_l, _r, pl, l, m) + query(_l, _r, pr, m, r);
    }    
};    

struct Node {// monoid
    int x, y;
    
    Node() : x(0x3f3f3f3f), y(-0x3f3f3f3f) {} // write your own identity
    Node(int _x, int _y) : x(_x), y(_y) {}
    Node(const Node& _r) : x(_r.x), y(_r.y) {}// write your own
    Node& operator = (const Node& _r) {
        x = _r.x; // write your own
        y = _r.y;
        return *this;
    }
    Node& operator += (const Node& _r) {
        x = min(x, _r.x); // write your own  !! may not communitative
        y = max(y, _r.y);
        return *this;
    }
    friend Node operator + (const Node& _lhs, const Node& _rhs) {
        return Node(_lhs) += _rhs; // derive from +=
    }
};

using Seg=Seglazy<Node, int>;
const int N = 1e6+10; 
void solve() {
    int n; cin >> n;
    string s; cin >> s;
    vector<int> a(n);
    int pos = 0;
    Seg seg;
    for (auto& p: seg.v) {
        p = {0,0};
    }
    for (char x: s) {
        if (x == 'L') {
            if (pos > 0)pos--;
        } else if (x == 'R') {
            pos++;
        } else if (x == '(') {
            if (a[pos] != 1) {
                int delta = 1 - a[pos]; a[pos] = 1;
                seg.update(pos, N, delta);
            }
        } else if (x == ')') {
            if (a[pos] != -1) {
                int delta = -1 - a[pos]; a[pos] = -1;
                seg.update(pos, N, delta);
            }
        } else {
            if (a[pos] != 0) {
                int delta = -a[pos]; a[pos] = 0;
                seg.update(pos, N, delta);
            }
        }

        auto res = seg.query(0, N);
        if (res.x == 0 && seg.query(n,n+1).x == 0) {
            cout << res.y << ' ';
        } else {
            cout << "-1 ";
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
