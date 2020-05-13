#include <bits/stdc++.h>

using namespace std;
#define LOCAL
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
#define dbg(args...) 2020
#endif

struct PersistentDsu {
#define sm (sl+(sr-sl)/2)
#define cl tr[v].ch[0]
#define cr tr[v].ch[1]
#define pa tr[v].p
#define rk tr[v].r
    using Ptr = int;
    using Index = int;
    int n;
    int* a;
    struct Node {
        Ptr ch[2] = {};
        Index p;
        int r = 0; // here rank=depth, one can modify to size.
        int val;
    };
    vector<Node> tr;
    PersistentDsu(int _n, int m, int* _a) : n(_n), a(_a) {
        tr.reserve(2*n + m*64 + 1024); // (2n + mlogn)
        // upd, upd1
        cn();
        build(0, n);
    }
    Ptr vc = 0;
    inline Ptr cn() {
        tr.emplace_back();
        return vc++;
    }
    inline Ptr cp(Ptr i) {
        tr.push_back(tr[i]); // not safe
        return vc++;
    }
    Ptr build(Index sl, Index sr) {
        auto v = cn();
        if (sr-sl == 1) { 
            pa = sl;
            tr[v].val = a[sl];
            return v;
        }
        cl = build(sl, sm);
        cr = build(sm, sr);
        return v;
    }
    // pa[x] = p
    Ptr update(Ptr pv, Index x, Index p, Index sl, Index sr) {
        auto v = cp(pv);
        if (sr-sl == 1) {
            pa = p;
            return v;
        }
        x < sm ? cl = update(cl,x,p,sl,sm) : cr = update(cr,x,p,sm,sr);
        return v;
    }
    // find v c-to x, i.e. store info pa[x], since we might other info
    Ptr query(Ptr v, Index x, Index sl, Index sr) {
        if (sr-sl == 1) return v;
        return x < sm ? query(cl,x,sl,sm) : query(cr,x,sm,sr);
    }
    // ++rk[x] of version-v
    // Warning: changed pv too. might TLE if reset. might need update-style
    void add(Ptr v, Index x, Index sl, Index sr) {
        if (sr-sl == 1) {
            ++rk; return;
        }
        x < sm ? add(cl,x,sl,sm) : add(cr,x,sm,sr);
    }
    
    Ptr update1(Ptr pv, Index x, Index p, Index sl, Index sr) {
        auto v = cp(pv);
        if (sr-sl == 1) {
            tr[v].val = p;
            return v;
        }
        x < sm ? cl = update1(cl,x,p,sl,sm) : cr = update1(cr,x,p,sm,sr);
        return v;
    }
    Ptr update(Ptr pv, Index x, Index p) { return update(pv,x,p,0,n); }
    Ptr query(Ptr v, Index x) { return query(v,x,0,n); }
    void add(Ptr v, Index x) { add(v,x,0,n); }
    // find root pa[x]=x, still return v not pa.
    Ptr find(Ptr _, Index x) {
        auto v = query(_,x);
        return pa == x ? v : find(_,pa);
    }
    Ptr join(Ptr _, Index x, Index y) {
        x = find(_,x);
        y = find(_,y);
        if (tr[x].p == tr[y].p) return _;
        if (tr[x].r < tr[y].r) swap(x,y);
        auto v = update(_,tr[y].p,tr[x].p);
        //tr[x].val = min(tr[x].val, tr[y].val); // need update-style
        if (tr[x].val > tr[y].val)
            v = update1(v, tr[x].p, tr[y].val, 0,n);
        if (tr[x].r == tr[y].r) ++tr[x].r;//add(v,tr[x].p); // same
        return v;
    }
    bool check(Ptr _, Index x, Index y) {
        x = find(_,x);
        y = find(_,y);
        return tr[x].p == tr[y].p;
    }
    int ans(Ptr _, Index x) {
        x = find(_,x);
        //cerr<<"pa:"<<tr[x].p<<endl;
        return tr[x].val;
    }
    void view() {
        dbg("!");
        for (int i = 1; i < vc; i++) {
            dbg(tr[i].p, tr[i].val);
        }
    }
#undef sm
#undef cl
#undef cr
#undef pa
#undef rk
};
struct State {
    int d,x;
    State() {}
    State(int _d, int _x) : d(_d), x(_x) {}
    bool operator<(const State& _oth) const {
        return d > _oth.d;
    }
};
// max 76/100, 4/16 TLE
void solve() {
    int n,m;
    cin >> n >> m;
    vector<tuple<int,int,int>> es(m);
    vector<vector<pair<int,int>>> g(n);
    vector<int> Hs(m);
    for (int i = 0; i < m; i++) {
        int x,y,z,h;
        cin >> x >> y >> z >> h;
        --x;--y;
        es[i] = {x,y,h};
        g[x].emplace_back(y, z);
        g[y].emplace_back(x, z);
        Hs[i] = h;
    }

    vector<int> d(n,2e9+10);
    priority_queue<State> pq;
    pq.emplace(d[0]=0, 0);
    while (!pq.empty()) {
        auto _ = pq.top(); pq.pop();
        int z = _.d, x = _.x;
        if (d[x] < z) continue;
        for (auto [y,w]: g[x]) {
            if (d[y] > z+w) {
                d[y] = z+w;
                pq.emplace(d[y],y);
            }
        }
    }

    sort(Hs.begin(), Hs.end());
    Hs.erase(unique(Hs.begin(), Hs.end()), Hs.end());
    auto pos = [&](int x){
        return lower_bound(Hs.begin(), Hs.end(), x) - Hs.begin();
    };
    int sz = Hs.size();
    vector<vector<pair<int,int>>> evs(sz);
    for (auto [x,y,h]:es) {
        evs[pos(h)].emplace_back(x, y);
    }
    PersistentDsu dsu(n,m, &d[0]);
    vector<int> roots(sz + 1);
    roots[sz] = 1;
    //dsu.view();
    for (int i = sz-1; i >= 0; i--) {
        roots[i] = roots[i+1];
        for (auto [x,y]:evs[i]) {
            roots[i] = dsu.join(roots[i], x,y);
        }
        //dsu.view();
    }
//dbg(roots);

    int las = 0;
    int q, K, S;
    cin >> q >> K >> S;
    while (q--) {
        int x, h;
        cin >> x >> h;
        x = (0ll+x + K*las - 1) % n;
        h = (0ll+h + K*las) % (S+1);
        h = pos(h+1);
        //cerr<<":"<<h<<endl;
        las = dsu.ans(roots[h], x);
        cout << las << "\n";
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int T; cin >> T;
    for (int t = 0; t < T; t++) {
        solve();
    }
    return 0;
}
