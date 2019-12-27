#include <bits/stdc++.h>

using namespace std;

template <typename T>
struct Line {
    T k, b;
    Line() {}
    Line(const Line<T>& _r) : k(_r.k), b(_r.b) {}
    Line(T _k, T _b) : k(_k), b(_b) {}

    inline T eval(T x) const{
        return k*x + b;
    }
    // act like point
    Line<T>& operator-=(const Line<T>& _r) {
        k -= _r.k; b -= _r.b;
        return *this;
    }
    friend Line<T> operator-(const Line<T>& _lhs, const Line<T>& _rhs) {
        return Line<T>(_lhs) -= _rhs;
    }
   // T cross(const Line<T>& _r) {
   //     return k*_r.b - b*_r.k;
   // }
    // watch out whether overflow
    inline long double cross(const Line<T>& _r) const{
        return (long double) k*_r.b - (long double) b*_r.k;
    }
};

// when range [l, r), has property P~notP, want last P.
// when return l-1, means not found.
template <typename T>
T bs_last(T l, T r, function<bool (T)> f) {
    assert(l < r);
    T mid;
    while (l != r) {
        mid = l + (r-l)/2;
        if (f(mid)) {
            l = mid + 1;
        }else {
            r = mid;
        }
    }
    return r-1;
}
template <typename T>
struct Convex {// max
    vector<Line<T>> hull;

    inline void add_line(T k, T b) {
        // k must be monotonic
        Line<T> ln(k, b);
        // if k inc. <= 0
        while ((int) hull.size() > 1 && (ln - hull.back()).cross(ln - *(hull.rbegin()+1)) >= 0) {
            hull.pop_back();
        }
        hull.push_back(ln);
    }
    inline T query(T x) {
        int id = bs_last<int>(0, (int)hull.size(), [&](int i){
                if (i == 0) return true;
                return hull[i].eval(x) >= hull[i-1].eval(x);
                });
        return hull[id].eval(x);
    }
    int best_id;
    T best_x, best_res;
    inline T brute_query(T x) {
        assert(x>=best_x);
        if (x==best_x) return best_res;
        // hull dec. x->inc, id should dec.
        while (best_id > 0 && hull[best_id-1].eval(x) >= hull[best_id].eval(x)) {
            best_id--;
        }
        best_x = x;
        best_res = hull[best_id].eval(best_x);
        return best_res;
    }
    void clear() {
        hull.clear();
    }
};

using Ch=Convex<long long>;
using ll=long long;
const int BLOCK_SIZE = 256; 
struct Block {
    int L, R;
    int x;
    ll k[BLOCK_SIZE], b[BLOCK_SIZE];
    bool sorted;
    vector<int> ord;
    Ch ch;
    Block() {}
    Block(int _L, int _R) : L(_L), R(_R), x(0), sorted(false), ord(R-L){
        iota(ord.begin(), ord.end(), 0);
    }

    void build() {
        ch.clear();
        if (!sorted) {
            sort(ord.begin(), ord.end(), [&](auto& u, auto& v){
                return k[u] > k[v];
            });
            sorted = true;
        }
        for(int i: ord){
            ch.add_line(k[i], b[i]);
        }
        ch.best_id = ch.hull.size()-1;
        ch.best_x = -1ll;
    }

    void update(int l, int r, int dx) {
        assert(L <= l && r <= R);
        if (L==l && r==R) {
            x += dx; return;
        }
        for (int i = L; i < R; i++) {
            b[i-L] += k[i-L]*x;
        } x = 0;
        for (int i = l; i < r; i++) {
            b[i-L] += k[i-L]*dx;
        }
        build();
    }
    ll query(int l, int r) {
        assert(L <= l && r <= R);
        if (L==l && r==R) {
            ll res = ch.brute_query(x);
            //assert(ch.query(x) == res);
            return res;
        }
        ll mx = -(1ll<<62);
        for (int i = l; i < r; i++) {
            mx = max(mx, k[i-L]*x + b[i-L]);
        }
        return mx;
    }
};

struct HLD {
    int n;
    vector<vector<int>> g;
    vector<int> sz, pa, depth, sta, fin, heavy, top, tour;
    int tim;
    vector<int> a,b;
    vector<Block> bs[2];
    HLD(int _n) : n(_n)
        , g(n)
        , sz(n, 1)
        , pa(n, -1)
        , depth(n)
        , sta(n)
        , fin(n)
        , heavy(n, -1)
        , top(n)
        , a(n)
        , b(n)
        {
        tour.reserve(n);
        input(); 
    }

    inline void add(int u, int v) {
        g[u].emplace_back(v);
        g[v].emplace_back(u);
    }
    void input() {
        //for (int _ = 1; _ < n; _++) {
        //    int x,y;
        //    cin >> x >> y;
        //    --x; --y; // to 0-based
        //    add(x,y);
        //}
        for (int i = 1; i < n; i++) {
            int u; cin >> u;
            u--;
            g[u].push_back(i);
        }
        for (int i = 0; i < n; i++) {
            cin >> a[i];
        }
        for (int i = 0; i < n; i++) {
            cin >> b[i];
        }
    }

    void dfs(int u) {
        //if (pa[u] != -1) g[u].erase(find(g[u].begin(), g[u].end(), pa[u]));
        for (int& v: g[u]) {
            pa[v] = u;
            depth[v] = depth[u] + 1;
            // !
            a[v] += a[u];
            b[v] += b[u];
            dfs(v);
            sz[u] += sz[v];
            // heavy skew left, thus chain consective on sta
            if (sz[v] > sz[g[u][0]]) swap(v, g[u][0]);
        }
    }
    // sta*tour = I
    void hld(int u) {
        sta[u] = tim++;
        tour.emplace_back(u);
        for (int v: g[u]) {
            top[v] = (v == g[u][0] ? heavy[u] = v, top[u] : v); // #h=1
            //top[v] = (sz[v] >= (sz[u]+1)/2 ? heavy[u] = v, top[u] : v); // #h<=1
            hld(v);
        }
        fin[u] = tim;
    }
#define rep(i) for(int i=0;i<2;i++)
    void build(int root = 0) {
        dfs(root);
        tim = 0; top[root] = root; hld(root);
        for (int l = 0; l < n; l+=BLOCK_SIZE) {
            int r;
            rep(_)
            bs[_].emplace_back(l, r = min(n, l+BLOCK_SIZE));
            auto L = bs[0].back().L; assert(L==l);
            for (int i = l; i < r; i++) {
                bs[0].back().k[i-L] = b[tour[i]];
                bs[0].back().b[i-L] = b[tour[i]] * 1ll * a[tour[i]];
                bs[1].back().k[i-L] = -b[tour[i]];
                bs[1].back().b[i-L] = -b[tour[i]] * 1ll * a[tour[i]];
            }
            rep(_)
            bs[_].back().build();
        }
    }
    inline void across_light(int& v) {
        v = pa[top[v]];
    }
    int lca(int u, int v) {
        while (top[u] != top[v]) {
            sta[u] < sta[v] ? across_light(v) : across_light(u);
        }
        return sta[u] < sta[v] ? u : v;
    }

    using F = function<void(int,int)>; // range operation tim(0)-based [l..r)
    // [u..v]
    void for_v_path(int u, int v, F f) {
        while (true) {
            if (sta[u] > sta[v]) swap(u, v);
            f(max(sta[top[v]], sta[u]), sta[v]+1);
            if (top[u] == top[v]) return;
            across_light(v);
        }
    }
    void for_v_sub(int u, F f, bool exclude = 0) {
        f(sta[u] + exclude, fin[u]);
    }
    void update(int l, int r, int x) {
        for (int i = l/BLOCK_SIZE; l < r; i++) {
            int _r = min(r, bs[0][i].R);
            rep(_)
            bs[_][i].update(l, _r, x);
            l = _r;
        }
    }
    ll query(int l, int r) {
        ll mx = -(1ll<<62);
        for (int i = l/BLOCK_SIZE; l < r; i++) {
            int _r = min(r, bs[0][i].R);
            rep(_)
            mx = max(mx, bs[_][i].query(l, _r));
            l = _r;
        }
        return mx;
    }

    void process(int q) {
        while (q--) {
            int op, v;
            cin >> op >> v;
            v--;
            if (op == 1) {
                int x; cin >> x;
                for_v_sub(v, [&](int l, int r){update(l,r,x);});
            } else {
                ll x = -(1ll<<62);
                for_v_sub(v, [&](int l, int r){x=max(x, query(l,r));});
                cout << x << "\n";
            }
        }
    }
};

void solve() {
    int n,q;
    cin >> n >> q;
    HLD hld(n);
    hld.build();
    hld.process(q);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
