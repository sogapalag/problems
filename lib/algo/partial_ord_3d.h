#include <bits/stdc++.h>

using namespace std;
using ll=long long;

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

// suppose 1-dim is sorted as index
// one of x,y dim, should in range(~1e5), here we let it be y
// key idea is similar to 2d(inversion), merge sort by x, maintain y into tree
ll partial_ord_3d(vector<pair<int,int>>& a) {
#define x first
#define y second
    ll res = 0;
    const int MX = 100005; // max(a.y)
    Fenwick<int> f(MX);
    auto comp = [&](auto& u, auto& v){
        return u.x < v.x;
    };
    function<void(int,int)> divi = [&](int l, int r){
        if (r-l <= 1) return;
        int m = (l+r)>>1;
        divi(l, m); divi(m, r);
        int i = l;
        for (int j = m; j < r; j++) {
            while (i < m && a[i].x < a[j].x) {
                f.add(a[i++].y, 1);
            }
            res += f.query(a[j].y - 1);
        }
        // clear
        while (i > l) {
            f.add(a[--i].y, -1);
        }
        inplace_merge(a.begin() + l, a.begin() + m, a.begin() + r, comp);
    };
    divi(0, a.size());
    return res;
#undef x
#undef y
}
