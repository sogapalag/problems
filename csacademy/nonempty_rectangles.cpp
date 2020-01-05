#include <bits/stdc++.h>

using namespace std;

template <typename T=int>
struct Compress {
    map<T, int> id;
    vector<T> num;

    Compress(vector<T> v) {
        sort(v.begin(), v.end());
        v.erase(unique(v.begin(), v.end()), v.end());
        num = v;
        for (int i = 0; i < (int)num.size(); i++) {
            id[num[i]] = i;
        }
    }

    inline int get_id(T x) {
        assert(id.count(x));
        return id[x];
    }
    inline T get_num(int i) {
        assert(0 <= i && i < num.size());
        return num[i];
    }
};

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
        for (int i = n-1; i > 0; i--) {
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
    Node() : x(-0x3f3f3f3f) {} // DO!! identity
    Node(int _x) : x(_x) {} // DO!! identity
    Node(const Node& _r) : x(_r.x) {}// DO!! set
    Node& operator = (const Node& _r) {// DO!! set
        x = _r.x;
        return *this;
    }
    Node& operator += (const Node& _r) {// DO!! may not communitative
        x = max(x, _r.x);
        return *this;
    }
    friend Node operator + (const Node& _lhs, const Node& _rhs) {
        return Node(_lhs) += _rhs; // derive from +=
    }
};

typedef Segtree<Node> Seg;

struct Point {
    int x, y;
    Point() {}
    Point(int _x, int _y) : x(_x), y(_y) {}
    bool operator<(const Point& _oth) const {
        return y < _oth.y || (y==_oth.y && x < _oth.x);
    }
};


// sweep by inc y, then inc x
// let xl,yl be 'left' with same y/x
// valid iff no point strictly inside this rect.
bool ck(vector<Point> a) {
    int n = a.size();
    sort(a.begin(), a.end());
    Seg seg(n);
    for (int i = 0; i < n; i++) {
        int xl = (i>0 && a[i-1].y==a[i].y) ? a[i-1].x : -1;
        int mx = seg.query(xl+1, a[i].x).x;
        int yl = seg.query(a[i].x, a[i].x+1).x;
        if (mx > yl) return false;
        seg.update(a[i].x, a[i].y);
    }
    return true;
}

void solve() {
    int n; cin >> n;
    vector<Point> a(n);
    vector<int> Xs(n);
    for (int i = 0; i < n; i++) {
        int x,y;
        cin >> x >> y;
        Xs[i] = x;
        a[i] = {x,y};
    }
    Compress<int> comp(Xs);
    for (int i = 0; i < n; i++) {
        a[i].x = comp.get_id(a[i].x);
    }
    
    if (ck(a)) {
        for (auto& p: a) {
            p.y = -p.y;
        }
        if (ck(a)) {
            cout << "1\n"; return;
        }
    }
    cout << "0\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int t; cin >> t;
    while(t--)solve();
    cout << endl;
}
