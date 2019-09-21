#include <bits/stdc++.h>

using namespace std;
using ll=long long ;
const long long INF = 0x3f3f3f3f3f3f3f3f;
template <typename T=int>
struct Segtree {
    int n; // leaf [n, 2n), view as original [0, n)
    int sz_v;
    const T ID;
    vector<T> v; //tree
    
    Segtree(int _n = 100005) : n(_n), sz_v(n<<1), ID() {
        v.resize(sz_v);
    }
    void init() {// set leaf value
        for (int i = 0; i < n; i++) {
            // v[i+n] = raw[i];
        }
        build();
    }
    void build() {
        for (int i = n-1; i >= 0; i--) {
            v[i] = v[i<<1] + v[i<<1|1];
        }
    }
    inline void update(int p, T val) {
        assert(p>=0);
        for (v[p += n] += val; p >>= 1;) {
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
};

struct Node {// monoid
    ll x;
    Node() : x(INF) {} // DO!! identity
    Node(int _x): x(_x) {}
    Node(const Node& _r) : x(_r.x) {}// DO!! set
    Node& operator = (const Node& _r) {// DO!! set
        x = _r.x;
        return *this;
    }
    Node& operator += (const Node& _r) {// DO!! may not communitative
        x = min(x, _r.x);
        return *this;
    }
    friend Node operator + (const Node& _lhs, const Node& _rhs) {
        return Node(_lhs) += _rhs; // derive from +=
    }
};

typedef Segtree<Node> Seg;

void solve() {
    int n, k;
    cin >> n >> k;
    string S; cin >> S;
    vector<vector<pair<int,int>>> g(n+1);
    for (int i = 1; i <= n; i++) {
        int l = i, r = i;
        if (S[i-1] == '1') {
            l = max(1, i-k);
            r = min(n, i+k);
        }
        g[r].emplace_back(l, i);
    }
    Seg s(n+1);
    s.update(0, Node(0));
    for (int r = 1; r <= n; r++) {
        for (auto& p: g[r]) {
            int l,cost;
            tie(l,cost) = p;
            auto crt = s.query(l-1, r+1);
            crt.x += cost;
            s.update(r, crt);
        }
    }
    ll res = s.query(n, n+1).x;
    cout << res;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
