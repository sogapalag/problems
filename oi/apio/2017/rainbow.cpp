#include <bits/stdc++.h>

using namespace std;

template <typename T=int>
struct Fenwick {
    int n;
    vector<T> v;
    
    Fenwick(int size = 100005) : n(size), v(n+1, 0) {}
    inline void add(int p, T val) {
        for (; p <= n; p += (p&-p)) { v[p] += val; }
    }
    inline T query(int p) {
        T tmp = 0;
        for (; p > 0; p -= (p&-p)) { tmp += v[p]; }
        return tmp;
    }
    inline T query(int l, int r) {
        return query(r) - query(l-1);
    }
};

// Warning: ensure y in range [1..n]
// support add (x,y) +val. query rect-sum
struct SparseCounter2dOffline {
    using X = int;
    using V = int;

    int n;
    Fenwick<V> f;
    struct Event {
        X x; int y;
        V v;
        int t; // t<0 update
        Event(X _x, int _y, V _v, int _t) : x(_x), y(_y), v(_v), t(_t) {}
        bool operator<(const Event& _oth) const {
            return x < _oth.x;
        }
    };
    vector<Event> evs;
    int qtim; // track query time
    SparseCounter2dOffline(int _n) : n(_n), f(n), qtim(0) {}
    
    // Warning: plz add chronologically
    void add_update(X x, int y, V val) {
        evs.emplace_back(x, y, val, -1);
    }
    // 1-based (,] <=> 0-based [,)
    void add_query(X xl, int yl, X xr, int yr) {
        evs.emplace_back(xl, yl, +1, qtim);
        evs.emplace_back(xl, yr, -1, qtim);
        evs.emplace_back(xr, yl, -1, qtim);
        evs.emplace_back(xr, yr, +1, qtim++);
    }
    vector<V> res;
    void divi(int l, int r) {
        if (r-l <= 1) return;
        int m = (l+r)>>1;
        divi(l, m); divi(m, r);
        int i = l;
        for (int j = m; j < r; j++) {
            while (i < m && evs[i].x <= evs[j].x) { //<=, since 1-based]
                if (evs[i].t < 0) f.add(evs[i].y, evs[i].v);
                i++;
            }
            if (evs[j].t >= 0) {
                res[evs[j].t] += f.query(evs[j].y) * evs[j].v;
            }
        }
        // clear
        while (i > l) {
            if (evs[--i].t < 0) f.add(evs[i].y, -evs[i].v);
        }
        inplace_merge(evs.begin() + l, evs.begin() + m, evs.begin() + r);
    }
    void solve() {
        res.resize(qtim);
        divi(0, evs.size());
    }
};


// https://loj.ac/problem/2310
// key: euler formula https://en.wikipedia.org/wiki/Euler_characteristic#Polyhedra
// V-E+F=1. for planer
// here, let V,Eh,Ev,F all top-left index(1,1)
// F=#river + #Compon
// note exception, 回shape(i.e. no river connect boarder). hole+1
void solve() {
    int n,m,len,q;
    cin >> n >> m >> len >> q;
    n += 10, m += 10;
    SparseCounter2dOffline V(m), Eh(m), Ev(m), F(m);
    // add river
    set<pair<int,int>> vs, ehs, evs, fs;
    int mix = n, mxx = 0;
    int miy = m, mxy = 0;
    auto insert = [&](int x, int y){
        mix = min(mix, x);
        mxx = max(mxx, x);
        miy = min(miy, y);
        mxy = max(mxy, y);
        vs.emplace(x,y);
        vs.emplace(x,y+1);
        vs.emplace(x+1,y);
        vs.emplace(x+1,y+1);
        ehs.emplace(x,y);
        ehs.emplace(x+1,y);
        evs.emplace(x,y);
        evs.emplace(x,y+1);
        fs.emplace(x,y);
    };
    int x0, y0;
    cin >> x0 >> y0;
    insert(x0,y0);
    if (len > 0) {
        string s; cin >> s;
        for (char c:s) {
            if (c=='N')x0--;
            if (c=='S')x0++;
            if (c=='W')y0--;
            if (c=='E')y0++;
            insert(x0,y0);
        }
    }
    for (auto [x,y]:vs) V.add_update(x,y,1);
    for (auto [x,y]:ehs) Eh.add_update(x,y,1);
    for (auto [x,y]:evs) Ev.add_update(x,y,1);
    for (auto [x,y]:fs) F.add_update(x,y,1);
    vector<int> res(q, 1);
    for (int i = 0; i < q; i++) {
        int x,y,u,v;
        cin >> x >> y >> u >> v;
        // 回
        if (x < mix && mxx < u &&
            y < miy && mxy < v) {
            res[i]++;
        }
        V.add_query(x,y,u,v);
        Eh.add_query(x,y-1,u,v);
        Ev.add_query(x-1,y,u,v);
        F.add_query(x-1,y-1,u,v);
    }
    V.solve();
    Eh.solve();
    Ev.solve();
    F.solve();

    for (int i = 0; i < q; i++) {
        res[i] -= V.res[i] - Eh.res[i] - Ev.res[i] + F.res[i];
        cout << res[i] << '\n';
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}
