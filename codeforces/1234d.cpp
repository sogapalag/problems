#include <bits/stdc++.h>

using namespace std;

template <typename T=int>
struct Segtree {
    int n; // leaf [n, 2n), view as original [0, n)
    int sz_v;
    const T ID;
    vector<T> v; //tree
    
    Segtree(const string& s) : n(s.size()), sz_v(n<<1), ID() {
        v.resize(sz_v);
        init(s);
    }
    void init(const string& s) {// set leaf value
        for (int i = 0; i < n; i++) {
            v[i+n].x = 1 << (s[i] - 'a');
        }
        build();
    }
    void build() {
        for (int i = n-1; i > 0; i--) {
            v[i] = v[i<<1] + v[i<<1|1];
        }
    }
    inline void update(int p, int val) {
        assert(p>=0);
        for (v[p += n].x = val; p >>= 1;) {
            v[p] = v[p<<1] + v[p<<1|1];
        }
    }
    inline T query(int l, int r) {
        T resl(ID), resr(ID);
        for (l += n, r += n; l < r; l >>= 1, r >>= 1) {
            if (l & 1) { resl = resl + v[l++]; }
            if (r & 1) { resr = v[--r] + resr; }
        }
        return resl + resr;
    }
    // Note only when range-assign, single-access not interfere. e.g max
    //inline void update(int l, int r, T val) {
    //    for (l += n, r += n; l < r; l >>= 1, r >>= 1){
    //        if (l & 1) { v[l++] = val; }
    //        if (r & 1) { v[--r] = val; }
    //    }
    //}
    //inline T query(int p){
    //    T res(ID);
    //    for (p += n; p > 0; p >>= 1) { res += v[p]; }
    //    return res;
    //}
};

struct Node {// monoid
    int x;
    Node() : x(0) {} // DO!! identity
    Node(const Node& _r) : x(_r.x) {}// DO!! set
    Node& operator = (const Node& _r) {// DO!! set
        x = _r.x;
        return *this;
    }
    Node& operator += (const Node& _r) {// DO!! may not communitative
        x |= _r.x;
        return *this;
    }
    friend Node operator + (const Node& _lhs, const Node& _rhs) {
        return Node(_lhs) += _rhs; // derive from +=
    }
};

typedef Segtree<Node> Seg;

void solve() {
    string s; cin >> s;
    Seg S(s);
    int q; cin >> q;
    while (q--) {
        int op; cin >> op;
        if (op == 1) {
            int i; char x;
            cin >> i >> x;
            S.update(i-1, 1<<(x-'a'));
        } else {
            int l, r;
            cin >> l >> r;
            int res = __builtin_popcount(S.query(l-1,r).x);
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
