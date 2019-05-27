#include <bits/stdc++.h>

using namespace std;

const int INF = 0x3f3f3f3f;

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
            v[i+n].x = INF;
        }
        build();
    }
    void build() {
        for (int i = n-1; i >= 0; i--) {
            v[i] = v[i<<1] + v[i<<1|1];
        }
    }
    // Note only when range-assign, single-access not interfere. e.g max
    inline void update(int l, int r, T val) {
        for (l += n, r += n; l < r; l >>= 1, r >>= 1){
            if (l & 1) { v[l++] = val; }
            if (r & 1) { v[--r] = val; }
        }
    }
    inline T query(int p){
        T res(ID);
        for (p += n; p > 0; p >>= 1) { res += v[p]; }
        return res;
    }
};

struct Node {// monoid
    int x;
    Node(int _=0) : x(INF) {} // DO!! identity
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
    int n, q;
    cin >> n >> q;
    vector<int> s(n), t(n), x(n);
    for (int i = 0; i < n; i++) {
        int a,b,c; cin >> a>>b >>c;
        s[i] = max(0, a-c);
        t[i] = max(0, b-c);
        x[i] = c;
    }
    vector<int> d(q);
    for (auto& i: d) {
        cin >> i;
    }
    // compress time
    vector<int> T; T.reserve(2*n+q+2);
    T.emplace_back(0);
    for (int i = 0; i < n; i++) {
        T.emplace_back(s[i]);
        T.emplace_back(t[i]);
    }
    for (int i = 0; i < q; i++) {
        T.emplace_back(d[i]);
    } T.emplace_back(INF);
    sort(T.begin(), T.end());
    T.erase(unique(T.begin(), T.end()), T.end());
    int sz = T.size();
    map<int, int> id;
    for (int i = 0; i < sz; i++) {
        id[T[i]] = i;
    }
    // since take min, so by decreasing-order update.
    // or don't sort, but make update take min instead of simple assign
    vector<int> id_by_x(n);
    iota(id_by_x.begin(), id_by_x.end(), 0);
    sort(id_by_x.begin(), id_by_x.end(), [&](int u, int v){
            return x[u] > x[v];
            });
    Seg seg(sz); seg.init();
    for (int i: id_by_x) {
        Node tmp; tmp.x = x[i];
        seg.update(id[s[i]], id[t[i]], tmp);
    }
    for (int i = 0; i < q; i++) {
        int res = seg.query(id[d[i]]).x;
        if (res == INF) res = -1;
        cout << res << "\n";
    }
}


int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
