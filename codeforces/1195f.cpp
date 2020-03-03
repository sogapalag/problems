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
        tr.push_back(tr[i]); // not safe
        return vc++;
    }
    PersistentSegmentTree(M _ID, Op _op, Index _SL, Index _SR)
        : ID(_ID), op(_op), SL(_SL), SR(_SR)
    {
        tr.reserve(1e7); // there is a intrinsic bug, if reserve not enough space, might RE
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

// if one know the conclusion of Minkowski sum. rest is simple
// two convex edges {E1} {E2}, the sum{E} has same direction of E1,E2.
// then remain is range count #unique
void solve() {
    int n; cin >> n;
    PersistentSegmentTree<int> pst(0, [](int u, int v){ return u+v; }, 0, n+1);
    vector<int> roots(n + 1);
    map<pair<int,int>, int> pre;
    vector<int> sum(n + 1);
    for (int i = 1; i <= n; i++) {
        int m; cin >> m;
        sum[i] = sum[i-1] + m;
        vector<pair<int, int>> a(m);
        for (int j = 0; j < m; j++) {
            cin >> a[j].first >> a[j].second; // j..
        }
        int ver = roots[i-1];
        for (int j = 0; j < m; j++) {
            int x = a[(j+1)%m].first - a[j].first;
            int y = a[(j+1)%m].second - a[j].second;
            if (!x && !y) continue;
            int g = __gcd(abs(x),abs(y));
            //cerr<<x<<' ' << y << ' ' << g<<endl;
            x /= g; y /= g;
            ver = pst.update(ver, pre[{x,y}], 1);
            pre[{x,y}] = i;
        }
        roots[i] = ver;
    }
    int q; cin >> q;
    while (q--) {
        int l,r;
        cin >> l >> r;
        // idiom, only one of [l..r] has pre<l, count which indicate #unique
        int res = pst.query(roots[r], 0, l) - sum[l-1];//pst.query(roost[l-1], 0, l);
        cout << res << "\n";
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}
