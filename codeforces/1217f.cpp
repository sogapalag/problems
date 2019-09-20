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

const int N = 1<<18; 
using pi=pair<int, int>;

struct Dsu {
    int n;
    vector<int> p;
    vector<int> r;
    vector<pi> histo;

    Dsu(int _n) { n = _n; p.resize(n); r.resize(n); init(); }
    inline void init() {
        for (int i = 0; i < n; i++) {
            p[i] = i;
            r[i] = 1;
        }
    }
    inline int find(int x) { // don't compress path
        while (x != p[x]) x = p[x];
        return x;
        //return p[x] == x ? x: p[x] = find(p[x]);
    }
    inline int join(int x, int y) {
        x = find(x); y = find(y);
        if (x == y) return 0;
        if (r[x] < r[y]) swap(x, y);
        histo.emplace_back(x, y);
        p[y] = x; r[x] += r[y];
        return 1;
    }
    inline int join(pi e) {
        return join(e.first, e.second);
    }
    void roll_back() {
        int x,y;
        tie(x,y) = histo.back(); histo.pop_back();
        r[x] -= r[y]; p[y] = y;
    }
    inline bool check(int x, int y) {
        return find(x) == find(y);
    }
    inline bool check(pi e) {
        return check(e.first, e.second);
    }
}d(N);

int n, q;
int last;
struct Opt {
    int t;
    pi p;
    Opt() {}
    Opt(int _t, int _x, int _y) : t(_t), p(_x,_y){}
} a[N];

map<pi, vector<int>> mp;
map<pi, bool> edge;
inline int shift(int x) {
    x++;
    return x>=n?x-n:x;
}
inline pi shift(pi p) {
    int x = shift(p.first), y = shift(p.second);
    if (x > y) swap(x, y);
    return {x, y};
}

template <typename T=vector<pi> >
struct Segtree {
    static const int H = 18; //20
    static const int SZ = 1<<H;
    int sz_v;
    vector<T> v; // tree
    
    Segtree() : sz_v(SZ<<1), v(sz_v) {
        //v.resize(sz_v);
        //d.resize(sz_v);
    }

    void update(int _l, int _r, const pair<int, int>& val, int p=1, int l=0, int r=SZ) {
        if (_r <= l || r <= _l) return;
        if (_l <= l && r <= _r) { // update by info
            v[p].push_back(val);
            return;
        }
        int m = (l+r)>>1, pl = p<<1, pr = p<<1|1;
        update(_l, _r, val, pl, l, m);
        update(_l, _r, val, pr, m, r);
    }
    void flip_edge(int i) {
        if (last) a[i].p = shift(a[i].p);
        dbg(last, i, a[i].p);
        edge[a[i].p] ^= 1;
    }
    void dfs(int p=1, int l=0, int r=SZ) {
        if ((p&1) && a[l].t == 1) flip_edge(l);
        // this l:0,1,2... in-order called, so edge[e] truly means edge existence
        int cnt = 0;
        for (auto& e: v[p]) {
            dbg(p, e);
            if (edge[e]) cnt += d.join(e);
        }
        if (r-l==1) {
            if (a[l].t == 2) {
                if (last) a[l].p = shift(a[l].p);
                dbg(last, l, a[l].p);
                last = d.check(a[l].p);
                cout << last;
            }
        }else {
            int m = (l+r)>>1, pl = p<<1, pr = p<<1|1;
            dfs(pl, l, m);
            dfs(pr, m, r);
        }
        // remove the seg edge-d, but edge mp info exist, so new seg calc is fine
        // why this, since we make edge-seg sparse to different layer, in-case long-range roll_back.
        while (cnt--) {
            d.roll_back();
        }
    }    
};    
void solve() {
    cin >> n >> q;
    for (int i = 0; i < q; i++) {
        int t,x,y;
        cin >> t >> x >> y;
        x--;y--;
        if (x > y) swap(x, y);
        a[i] = {t,x,y};
        mp[{x,y}].emplace_back(i);
        mp[shift({x,y})].emplace_back(i);
    }

    Segtree<> s;
    // for each pair(edge), cut into potential seg.
    // hence some flip can be done in higher layer, thus future roll_back is low-cost.
    for (auto& p: mp) {
        auto& v = p.second;
        v.emplace_back(q);
        int m = v.size();
        for (int i = 1; i < m; i++) {
            s.update(v[i-1], v[i], p.first);
        }
    }
    s.dfs();
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
