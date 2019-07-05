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

using ll=long long;

template <typename T, typename U>
struct Seglazy {
    static const int H = 17; //20
    static const int SZ = 1<<H;
    int sz_v;
    const T ID;  // identity
    const U UN;  // not info
    vector<T> v; // tree
    vector<U> d; // lazy
    
    Seglazy() : sz_v(SZ<<1), ID(), UN(-(1ll<<62)), v(sz_v), d(sz_v, UN) {
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
        dbg(p, v[p].x, d[p]);
        assert(v[p].x < d[p]);
        v[p].x = d[p];
        v[p].y = d[p] * len(p);
    }
    inline void store(int p, const U& val) {// do!! store info, careful!! info chain
        d[p] = val;
    }
    inline void push(int p) {
        apply(p);
        if (p < SZ) {
            store(p<<1, d[p]);
            store(p<<1|1, d[p]);
        }
        d[p] = UN;
    }
   // bool update(int _l, int _r, const U& val, int p=1, int l=0, int r=SZ) {
   //     if (d[p] != UN) push(p);
   //     if (_r <= l || r <= _l || l==r) return false;
   //     if (_l <= l && r <= _r && v[p].x < val) { // update by info
   //         dbg(l, r, v[p].x, val);
   //         dbg(_l, _r);
   //         store(p, val);
   //         push(p);
   //         return false;
   //     }
   //     if (r-l<=1) return true;
   //     int m = (l+r)>>1, pl = p<<1, pr = p<<1|1;
   //     bool done = update(_l, _r, val, pl, l, m) || update(_l, _r, val, pr, m, r);
   //     // here right not update, might cause below v wrong?? bug might be here..
   //     v[p] = v[pl] + v[pr];
   //     return done;
   // }
    void update(int _l, int _r, const U& val, int p=1, int l=0, int r=SZ) {
        if (d[p] != UN) push(p);
        if (_r <= l || r <= _l ) return;
        if (_l <= l && r <= _r) { // update by info
            store(p, val);
            push(p);
            return;
        }
        int m = (l+r)>>1, pl = p<<1, pr = p<<1|1;
        update(_l, _r, val, pl, l, m), update(_l, _r, val, pr, m, r);
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
    ll x, y;
    
    Node() : x(-(1ll<<62)), y(0) {} // write your own identity
    Node(ll _x, ll _y) : x(_x), y(_y) {}
    Node(const Node& _r) : x(_r.x), y(_r.y) {}// write your own
    Node& operator = (const Node& _r) {
        x = _r.x; y = _r.y; // write your own
        return *this;
    }
    Node& operator += (const Node& _r) {
        x = max(x, _r.x); // write your own  !! may not communitative
        y += _r.y;
        return *this;
    }
    friend Node operator + (const Node& _lhs, const Node& _rhs) {
        return Node(_lhs) += _rhs; // derive from +=
    }
};
// when range [l, r), has property P~notP, want last P.
// when return l-1, means not found.
template <typename T>
T bs_last(T l, T r, function<bool (T)> f) {
    assert(l < r);
    T mid;
    while (l != r) {
        mid = l + (r-l)/2;
        if (f(mid)) {
            l = mid + 1;
        }else {
            r = mid;
        }
    }
    return r-1;
}

using Seg=Seglazy<Node, ll>;

// well, log^2, but easy to impl.
void solve() {
    int n; cin >> n;
    vector<ll> a(n);
    for (auto& x: a) {
        cin >> x;
    }
    vector<ll> t(n); t[0] = 0;
    for (int i = 1; i < n; i++) {
        ll k; cin >> k;
        t[i] = t[i-1] + k;
    }
    vector<ll> cum(n+1); cum[0] = 0;
    for (int i = 1; i <= n; i++) {
        cum[i] = cum[i-1] + t[i-1];
    }
    Seg s;
    for (int i = 0; i < n; i++) {
        s.v[s.SZ+i] = {a[i]-t[i], a[i]-t[i]};
    }
    s.build();
    int q; cin >> q;
    while (q--) {
        string op; cin >> op;
        if (op[0] == '+') {
            int i, x; cin >> i >> x;
            if (x == 0) continue;
            ll b = s.query(i-1, i).x + x;
            int pos = bs_last<int>(i-1, n, [&](int r){
                    return s.query(r, r+1).x < b;
                    });
            s.update(i-1, pos+1, b);
        } else {
            int l, r; cin >> l >> r;
            ll res = s.query(l-1, r).y + cum[r] - cum[l-1];
            cout << res << "\n";
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
