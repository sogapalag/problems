#include <bits/stdc++.h>

using namespace std;

using ll=long long;

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
            v[p].x = val; // min(v[p].x, val); // not assign, mini
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

using Seg=Seglazy<Node, ll>;

// key idea, min-cut has special form, i.e. prefix L&R
// use seglazy to prep constant min. A[i]
void solve() {
    int n,m,q;
    cin >> n >> m >> q;
    // prep
    Seg seg; seg.assign(0,1, 0);
    vector<int> a(n);
    for (int i = 1; i < n; i++) {
        int y;
        cin >> a[i-1] >> y;
        seg.assign(i,i+1, y);
    }
    vector<vector<pair<int,int>>> g(n);
    for (int _ = 0; _ < m; _++) {
        int x,y,w;
        cin >> x >> y >> w;
        x--;
        g[x].emplace_back(y,w);
    }
    vector<ll> A(n);
    for (int i = 0; i < n; i++) {
        for (auto& _: g[i]) {
            int r, w;
            tie(r, w) = _;
            seg.update(0, r, w);
        }
        A[i] = seg.query(0, Seg::SZ).x;
    }

    multiset<ll> s;
    for (int i = 0; i < n; i++) {
        s.insert(a[i] + A[i]);
    }
    cout << *s.begin() << "\n";
    while (q--) {
        int i,x;
        cin >> i >> x;
        i--;
        s.erase(s.find(a[i]+A[i]));
        s.insert((a[i]=x) + A[i]);
        cout << *s.begin() << "\n";
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
