#include <bits/stdc++.h>

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
        tr.push_back(tr[i]);
        return vc++;
    }
    PersistentSegmentTree(M _ID, Op _op, Index _SL, Index _SR)
        : ID(_ID), op(_op), SL(_SL), SR(_SR)
    {
        tr.reserve(2e6);
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

    Ptr update(Ptr pv, Index p, const M& val) {
        return update(pv, p, val, SL, SR);
    }
    M query(Ptr v, Index l, Index r) {
        return query(v, l, r, SL, SR);
    }
    M query_all(Ptr v) const { return tr[v].x; }
};

const int N = 100005; 
vector<int> q[N];

void solve() {
    int n,k;
    cin >> n >> k;
    PersistentSegmentTree<int> pst(0, [](int u, int v){ return u+v; }, 0, n+1);
    vector<int> roots(n + 1);
    for (int i = 1; i <= n; i++) {
        int x; cin >> x;
        q[x].push_back(i);
        int pre = 0;
        int m = q[x].size();
        if (m > k) {
            //pre = q[x].front(); q[x].pop();
            pre = q[x][m-k-1];
        }
        roots[i] = pst.update(roots[i-1], pre, 1);
    }
    int res = 0;
    int q; cin >> q;
    while (q--) {
        int l,r;
        cin >> l >> r;
        l = (l+res)%n + 1;
        r = (r+res)%n + 1;
        if (l > r) swap(l, r);
        l--;
        res = pst.query(roots[r], 0, l+1) - l;
        cout << res << '\n';
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}
