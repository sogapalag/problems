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
using ll=long long;
// editor's consider x-r,x,x+r event.
// anyhow, sort by r dec. would work as well, since less r, [x-r,x-r] contain before y, y also contain x. 
// one way is brute force [q-k,q+k] since k~20, with ptr-seg.
// below is just simply transform it to sc2d count problem. k can be any.
void solve() {
    int n,k;
    cin >> n >> k;
    vector<int> Qs;
    vector<int> x(n), r(n), q(n);
    for (int i = 0; i < n; i++) {
        cin >> x[i] >> r[i] >> q[i];
        Qs.push_back(q[i]);
        Qs.push_back(q[i]-k-1);
        Qs.push_back(q[i]+k);
    }
    Compress<int> cq(Qs);
    vector<int> id(n);
    iota(id.begin(), id.end(), 0);
    sort(id.begin(), id.end(), [&](auto& u, auto& v){
        return r[u] > r[v];
    });
    SparseCounter2dOffline sc(cq.num.size());
    for (int _: id) {
        sc.add_query(x[_]-r[_]-1, cq.get_id(q[_]-k-1),
                     x[_]+r[_], cq.get_id(q[_]+k));
        sc.add_update(x[_], cq.get_id(q[_]), 1);
    }
    sc.solve();
    ll res = 0;
    for (auto& x: sc.res) {
        res += x;
    }
    cout << res;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}
