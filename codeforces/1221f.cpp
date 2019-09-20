#include <bits/stdc++.h>

using namespace std;

#undef LOCAL
string to_string(string s) { return '"' + s + '"'; }
string to_string(bool x) { return (x ? "T" : "F"); }
string to_string(const char* s) { return to_string((string)s); }
template <typename A, typename B>
string to_string(pair<A, B> p) { return "(" + to_string(p.first) + ", " + to_string(p.second) + ")"; }
template <typename V>
string to_string(V v) {
    bool f = true; string res = "[";
    for (const auto& x: v) {
        if (!f) res += ", ";
        f = false;
        res += to_string(x); } res += "]";
    return res;
}
void debug() { cerr << endl; }
template <typename H, typename... T>
void debug(H h, T... t) { cerr << " " << to_string(h); debug(t...); }
#ifdef LOCAL
#define dbg(args...) cerr<<"("<<#args<<") =", debug(args)
#else
#define dbg(args...) 2019
#endif

using ll=long long ;
const long long INF = 0x3f3f3f3f3f3f3f3f;
template <typename T=int>
struct Compress {
    map<T, int> id;
    vector<T> num;

    Compress(vector<T> v) {
        sort(v.begin(), v.end());
        v.erase(unique(v.begin(), v.end()), v.end());
        num = v;
        for (int i = 0; i < (int)num.size(); i++) {
            id[num[i]] = i;
        }
    }

    inline int get_id(T x) {
        assert(id.count(x));
        return id[x];
    }
    inline T get_num(int i) {
        assert(0 <= i && i < (int)num.size());
        return num[i];
    }
};
template <typename T, typename U>
struct Seglazy {
    static const int H = 20;// 2^19=5e5, but we use x,y compress together.
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
            v[p].x = max(v[p].x, val); // not assign, maxi
            v[p].l = _l;
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
    int l;
    
    Node() : x(-INF), l(-1) {} // write your own identity
    Node(ll _x, int _l) : x(_x), l(_l){}
    Node(const Node& _r) : x(_r.x), l(_r.l) {}// write your own
    Node& operator = (const Node& _r) {
        x = _r.x; // write your own
        l = _r.l;
        return *this;
    }
    Node& operator += (const Node& _r) {
        //x = max(x, _r.x); // write your own  !! may not communitative
        if (x < _r.x) {
            x = _r.x; l = _r.l;
        }
        return *this;
    }
    friend Node operator + (const Node& _lhs, const Node& _rhs) {
        return Node(_lhs) += _rhs; // derive from +=
    }
};

using Seg=Seglazy<Node, ll>;

struct Point {
    int x, y, c;
    Point() {}
    Point(int _x, int _y, int _c) : x(_x), y(_y), c(_c) {}
    bool operator<(const Point& _oth) const {
        return y < _oth.y;
    }
};

// consider fix r(or l), for some Point (x,y),  l<=x thus contain the Point, so range-add [0,x] +c
void solve() {
    int n; cin >> n;
    vector<Point> a(n);
    vector<int> XYs(2*n);
    for (int i = 0; i < n; i++) {
        int x,y,c;
        cin >> x >> y >> c;
        if (x > y) swap(x,y);
        a[i] = {x,y,c};
        XYs[i] = x;
        XYs[i+n] = y;
    }
    Compress<> c(XYs);
    int m = c.num.size();
    Seg s;
    for (int i = 0; i < m; i++) {
        s.assign(i,i+1, c.get_num(i));
    }
    sort(a.begin(), a.end());
    ll res = 0; int l = -1, r = -1;
    // process in y-> order
    int i = 0;
    while (i < n) {
        int I = i;
        while (i < n && a[i].y == a[I].y) {
            int ix = c.get_id(a[i].x);
            //int iy = c.get_id(a[i].y);
            s.update(0, ix+1, a[i].c); // seg l from [0,ix], contain [x,y]
            i++;
        }
        auto mx = s.query(0, c.get_id(a[I].y)+1);
        dbg(I, mx.x, mx.l, a[I].y);
        mx.x -= a[I].y;
        if (mx.x > res) {
            res = mx.x;
            l = c.get_num(mx.l);
            r = a[I].y;
        }
    }
    if (res == 0) {
        const int N = 1e9+1000;
        l = r = N;
    }

    cout << res << "\n";
    cout << l << ' '<< l <<' ' << r<< ' '<< r;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
