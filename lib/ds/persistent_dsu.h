#include <bits/stdc++.h>

using namespace std;
// verified by https://www.luogu.com.cn/problem/P3402
// key:
//   only leaf-ptr's value is meaningful. non-leaf only ch[0/1] used.
//   tree structure for persistent-use(restore)
//   each join actually modify one leaf's pa. but we create O(log) ptr, for restore current version
//   don't merge pa-path. rank ensure complexity
//
// SNIPPETS_START persistent_dsu
struct PersistentDsu {
#define sm (sl+(sr-sl)/2)
#define cl tr[v].ch[0]
#define cr tr[v].ch[1]
#define pa tr[v].p
#define rk tr[v].r
    using Ptr = int;
    using Index = int;
    int n;
    struct Node {
        Ptr ch[2] = {};
        Index p;
        int r = 0; // here rank=depth, one can modify to size.
    };
    vector<Node> tr;
    PersistentDsu(int _n) : n(_n) {
        tr.reserve(n*64); // (2n + mlogn)
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
    // Warning: changed pv's, might TLE If reset.
    void add(Ptr v, Index x, Index sl, Index sr) {
        if (sr-sl == 1) {
            ++rk; return;
        }
        x < sm ? add(cl,x,sl,sm) : add(cr,x,sm,sr);
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
        if (tr[x].r == tr[y].r) ++tr[x].r;//add(v,tr[x].p); // same
        return v;
    }
    bool check(Ptr _, Index x, Index y) {
        x = find(_,x);
        y = find(_,y);
        return tr[x].p == tr[y].p;
    }
#undef sm
#undef cl
#undef cr
#undef pa
#undef rk
};
// SNIPPETS_END
