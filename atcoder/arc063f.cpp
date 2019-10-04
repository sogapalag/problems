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
    
    Node() : x(0) {} // write your own identity
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
using Point = pair<int, int>;
#define X first
#define Y second

// +1-1@#^&@ becareful
// here the seg(i) means i as left-boarder, i.e. contribute -x_i, 
// up calcel h, dn not
int calc(int w, int h, vector<Point>& a) {
    int n = a.size();
    sort(a.begin(), a.end());
    Seg s;
    vector<int> up, dn;
    int res = 0;
    s.update(0, n+3, h);
    for (int i = 1; i < n; i++) {
        int x,y;
        tie(x,y) = a[i];
        res = max(res, x + s.query(0, i).x);
        // if choose i, contributes.
        s.update(i, i+1, -x);
        // upd ..,i) range
        if (y >= h/2) {
            int l,r=i;
            l = up.empty()?0:up.back();
            s.update(l, r, y-h);
            while (!up.empty() && a[r=up.back()].Y >= y) {
                up.pop_back();
                l = up.empty()?0:up.back();
                s.update(l, r, y-a[r].Y);
                r = l; 
            }
            up.emplace_back(i);
        } else {
            int l,r=i;
            l = dn.empty()?0:dn.back();
            s.update(l, r, -y);
            while (!dn.empty() && a[r=dn.back()].Y <= y) {
                dn.pop_back();
                l = dn.empty()?0:dn.back();
                s.update(l, r, a[r].Y-y);
                r = l;
            }
            dn.emplace_back(i);
        }
    }
    return res;
}

// we consider half perimeter
// since lower bound max(H,W)+1. implies rect crossed by x=W/2 or y=H/2.
// wlog consider y=H/2, for a pair x boarder, just let between, y>H/2 choose above, <H/2 choose below.
// then we must cover the optimal. (note =H/2 may need additional consideration, but I saw many AC without.)
// iter right-boarder, left-boarder contribute -x, upd to seglazy.
// let hi = min(>H/2), lo = max(<H/2), contribute hi-lo, we can split it two part too.
//   then use up_stack maintain idx that y>=H/2, update new idx in could_cover_range.
void solve() {
    int W, H, n;
    cin >> W >> H >> n;
    vector<Point> a(n+2);
    a[0] = {0,0};
    for (int i = 1; i <= n; i++) {
        cin >> a[i].X >> a[i].Y;
    }
    a[n+1] = {W, H};
    int res = calc(W, H, a);
    for (auto& p: a) {
        swap(p.X,p.Y);
    }
    res = max(res, calc(H, W, a));
    res <<= 1;
    cout << res;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
