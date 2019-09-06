#include <bits/stdc++.h>

using namespace std;

const long long INF = 0x3f3f3f3f3f3f3f3f;
template <typename T=int>
struct Segtree {
    int n; // leaf [n, 2n), view as original [0, n)
    int sz_v;
    const T ID;
    vector<T> v; //tree
    
    Segtree(int _n = 100005) : n(_n), sz_v(n<<1), ID() {
        v.assign(sz_v, 0);
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
        for (v[p += n] = val; p >>= 1;) {
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

using ll=long long ;
struct Node {// monoid
    ll x[2];
    Node(int _=0) : x{INF,INF} {} // DO!! identity
    Node(const Node& _r) : x{_r.x[0], _r.x[1]} {}// DO!! set
    Node(ll _a, ll _b) : x{_a,_b} {}
    Node& operator = (const Node& _r) {// DO!! set
        x[0] = _r.x[0];
        x[1] = _r.x[1];
        return *this;
    }
    Node& operator += (const Node& _r) {// DO!! may not communitative
        ll a=min(x[0],_r.x[0]);
        ll b=min(max(x[0],_r.x[0]), min(x[1],_r.x[1]));
        x[0]=a, x[1]=b;
        return *this;
    }
    friend Node operator + (const Node& _lhs, const Node& _rhs) {
        return Node(_lhs) += _rhs; // derive from +=
    }
};

typedef Segtree<Node> Seg;
const int L = 10; 
// maintain digit's setted two smallest x
// since candidate is some digit as edge, two x will be unbalanced
void solve() {
    int n,q;
    cin >> n >> q;
    vector<Seg> s(L, n);
    auto upd = [&](int i, ll x){
        ll t = x;
        for (int j = 0; j < L; j++) {
            if (t%10) {
                s[j].update(i, Node{x, INF});
            } else {
                s[j].update(i, Node{INF,INF});
            }
            t/=10;
        }
    };
    auto qry = [&](int l, int r){
        ll mi = INF<<1;
        for (int j = 0; j < L; j++) {
            auto p = s[j].query(l-1, r);
            ll sum = p.x[0] + p.x[1];
            //cout << j << '#' << sum <<"\n";
            mi = min(mi, sum);
        }
        if (mi >= INF) return -1ll;
        return mi;
    };
    for (int i = 0; i < n; i++) {
        ll x; cin >> x;
        upd(i,x);
    }
    while (q--) {
        int tp; cin >> tp;
        if (tp == 1) {
            int i; ll x;
            cin >> i >> x;
            upd(i-1, x);
        } else {
            int l,r;
            cin >> l >> r;
            cout << qry(l,r) << "\n";
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
