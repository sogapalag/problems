#include <bits/stdc++.h>
#include "holiday.h"

using namespace std;
using ll=long long;
int sorted[100005];
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
        // Node=20B
        // 64MB limit
        tr.reserve(2e6); // WARNING: there's an intrinsic bug, if don't reserve enough space, might RE
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
#define sz first
#define sum second
    ll get_k_largest(Ptr pl, Ptr pr, int k, Index sl, Index sr) {
        if (sr-sl == 1) return k *1ll* sorted[sl];
        int sm = sl + (sr-sl)/2;
        int d = k - (trc(pr).x.sz - trc(pl).x.sz); // k - ()
        if (d <= 0) return get_k_largest(rc(pl), rc(pr), k, sm, sr);
        else return get_k_largest(lc(pl), lc(pr), d, sl, sm) + trc(pr).x.sum-trc(pl).x.sum;
    }
    ll get_k_largest(Ptr pl, Ptr pr, int k) {
        return get_k_largest(pl, pr, k, SL, SR);
    }

    Ptr update(Ptr pv, Index p, const M& val) {
        return update(pv, p, val, SL, SR);
    }
    M query(Ptr v, Index l, Index r) {
        return query(v, l, r, SL, SR);
    }
    M query_all(Ptr v) const { return tr[v].x; }
};

using M = pair<int,ll>;
PersistentSegmentTree<M> pst({}, [](M u, M v){return M{u.sz+v.sz, u.sum+v.sum};}, 0, 1<<17); // 64MB tight
const int N = 100005; 
int root[N];
int n,S,D;
int* a;
ll res = 0;
void divi(int l, int r, int dl, int dr) {
    if (l >= r) return;
    int m = (l+r)/2;
    // brute-force
    ll mx = -1; int id = -1; // tmp could 0.., defaul set -1
    for (int i = dl; i < dr; i++) {
        int walk = i-m + min(i-S, S-m);
        int k = D - walk;
        if (k > 0) {
            k = min(k, i-m+1);
            ll tmp = pst.get_k_largest(root[m], root[i+1], k);
            if (mx < tmp) {
                mx = tmp; id = i;
            }
        } else break;
    }
    res = max(res, mx);
    assert(id != -1); //! k=0 could result, 
    divi(l, m, dl, id+1); divi(m+1, r, id, dr);
}
// wlog consider [b s  c] i.e. s->b->c
// a solution calc 4 cases, f(i): s walk right(i days) best. f'(i): s->r->s (i days) best
// above 4 cases are similar. but we can actually calc 1 case,
//   i.e. b->c. since(c->b is same, we greedy use min(bs,sc) to waste the walk)
// i.e. optim-form, we first walk s->b, then for each b consider in remain days go-right best.
// note once we decide how many days used for walking, the problem is ask range best-k sum. solved by PST
// key: i<j => d(i)<=d(j), where d(i) is right-end when f(i) optim.
//    and d<d' => d(i) <= d'(i), where d<d' means start-pos
//    => d(i) <= d'(j)
//   thus we can divi, each time brute-force calc f(mid), d(mid) first
long long int findMaxAttraction(int _n, int _S, int _D, int _a[]) {
    // ..D can=0
    if (_D==0) return 0ll;
    n=_n,S=_S,D=_D,a=_a;
    for (int i = 0; i < n; i++) {
        sorted[i] = a[i];
    }
    sort(sorted, sorted+n);
    int tot = unique(sorted, sorted+n)-sorted;
    for (int i = 0; i < n; i++) {
        int p = lower_bound(sorted, sorted+tot, a[i]) - sorted;
        root[i+1] = pst.update(root[i], p, {1, a[i]});
    }
    divi(max(0, S-D+1), S+1, S, n); // S-D, k=0
    return res;
}
