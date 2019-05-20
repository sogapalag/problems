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

void solve() {
    int n; cin >> n;
    struct Arr {
        int x, id;
    };
    vector<Arr> a(n+1);
    for (int i = 1; i <= n; i++) {
        cin >> a[i].x;
        a[i].id = i;
    }
    sort(a.begin()+1, a.end(), [](auto& u, auto& v){
            return u.x > v.x;
            });
    int q; cin >> q;
    struct Qry {
        int l, r, k, id;
    };
    vector<Qry> b(q+1);
    for (int i = 1; i <= q; i++) {
        cin >> b[i].l >> b[i].r >> b[i].k;
        b[i].id = i;
    }
    sort(b.begin()+1, b.end(), [](auto& u, auto& v){
            return u.k > v.k;
            });

    Fenwick<int> f(n);
    vector<int> res(q+1);
    int j = 1;
    for (int i = 1; i <= q; i++) {
        while (j <= n && a[j].x > b[i].k) {
            f.add(a[j++].id, 1);
        }
        res[b[i].id] = f.query(b[i].l, b[i].r);
    }
    for (int i = 1; i <= q; i++) {
        cout << res[i] << '\n';
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
