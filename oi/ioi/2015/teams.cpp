#include <bits/stdc++.h>
#include "teams.h"

using namespace std;

template <typename M>
struct PersistentSegmentTree {
    using Op = function<M(const M&, const M&)>;
    using Ptr = int;
    using Index = int;
    M ID;
    Op op;
    Index SL, SR;
    struct Node {
        Ptr ch[2] = {};
        M x;
        Node(M _x) : x(_x) {}
    };
    vector<Node> tr;
    Ptr vc = 0; // version count
    // create node
    inline Ptr cn(const M& val) {
        tr.emplace_back(val);
        return vc++;
    }
    inline Ptr cp(const Ptr& i) {
        tr.push_back(tr[i]); // not safe
        return vc++;
    }
    PersistentSegmentTree(M _ID, Op _op, Index _SL, Index _SR)
        : ID(_ID), op(_op), SL(_SL), SR(_SR)
    {
        // TODO
        tr.reserve(3e7); // WARNING: there's an intrinsic bug, if don't reserve enough space, might RE
        cn(ID);
    }
    inline void pull(Ptr i) { tr[i].x = op(tr[ tr[i].ch[0] ].x, tr[ tr[i].ch[1] ].x); }
    Ptr update(Ptr pv, Index p, const M& val, Index sl, Index sr) {
        if (sr - sl == 1) return cn(op(tr[pv].x, val));
        Index sm = sl + (sr-sl)/2;
        Ptr ptr = cp(pv);
        if (p < sm) tr[ptr].ch[0] = update(tr[ptr].ch[0], p, val, sl, sm);
        else        tr[ptr].ch[1] = update(tr[ptr].ch[1], p, val, sm, sr);
        pull(ptr);
        return ptr;
    }
    M query(Ptr v, Index l, Index r, Index sl, Index sr) {
        if (r <= sl || sr <= l) return ID;
        if (l <= sl && sr <= r) return tr[v].x;
        Index sm = sl + (sr-sl)/2;
        return op(query(tr[v].ch[0], l, r, sl, sm),
                  query(tr[v].ch[1], l, r, sm, sr));
    }
#define lc(x) tr[x].ch[0]
#define rc(x) tr[x].ch[1]
#define tlc(x) tr[lc(x)]
#define trc(x) tr[rc(x)]
    // largest
    int kth(Ptr pl, Ptr pr, int k, Index sl, Index sr) {
        if (sr-sl == 1) return sl;
        int sm = sl + (sr-sl)/2;
        int d = k - (trc(pr).x - trc(pl).x); // k - ()
        if (d <= 0) return kth(rc(pl), rc(pr), k, sm, sr);
        else return kth(lc(pl), lc(pr), d, sl, sm);
    }
    int kth(Ptr pl, Ptr pr, int k) {
        return kth(pl, pr, k, SL, SR);
    }

    Ptr update(Ptr pv, Index p, const M& val) {
        return update(pv, p, val, SL, SR);
    }
    M query(Ptr v, Index l, Index r) {
        return query(v, l, r, SL, SR);
    }
    M query_all(Ptr v) const { return tr[v].x; }
};
const int N = 1<<19; 
PersistentSegmentTree<int> pst(0, [](int u, int v){ return u+v; }, 0, 1<<19);
int roots[N];
void init(int n, int l[], int r[]) {
    vector<vector<int>> g(n+1);
    for (int i = 0; i < n; i++) {
        g[l[i]].push_back(r[i]);
    }
    for (int i = 1; i <= n; i++) {
        roots[i] = roots[i-1];
        for (int x:g[i]) {
            roots[i] = pst.update(roots[i], x, 1);
        }
    }
}
struct Reso {
    int x, y, z;
    Reso() {}
    Reso(int _x, int _y, int _z) : x(_x), y(_y), z(_z) {}
    bool operator<(const Reso& _oth) const {
        return y < _oth.y;
    }
};

// pst for 2d query
// stk for acquire resource
//   when <= x (up), >= y (down), can get z(down) free
int can(int n, int a[]) {
    sort(a, a+n);
    vector<Reso> stk;
    for (int _ = 0; _ < n; _++) {
        int y = a[_];
        while (!stk.empty() && stk.back().y < y) {
            stk.pop_back();
        }
        int has = pst.query(roots[y], y, N)
            + (stk.empty()? 0: -pst.query(roots[stk.back().x], y, N) + stk.back().z);
        has -= y;
        if (has < 0) return 0;
        int need = pst.kth(roots[stk.empty()?0:stk.back().x], roots[y], has - (stk.empty()?0:stk.back().z));
        while (!stk.empty() && stk.back().y < need) {
            stk.pop_back();
            need = pst.kth(roots[stk.empty()?0:stk.back().x], roots[y], has - (stk.empty()?0:stk.back().z));
        }
        stk.emplace_back(y, need, has);
    }
    return 1;
}

//int main() {
//    int n; cin >> n;
//    int a[10], b[10];
//    for (int i = 0; i < n; i++) {
//        cin >> a[i] >> b[i];
//    }
//    init(n,a,b);
//    int q; cin >> q;
//    while (q--) {
//        int m; cin >> m;
//        for (int i = 0; i < m; i++) {
//            cin >> a[i];
//        }
//        cout << can(m,a) << "\n";
//    }
//    return 0;
//}
