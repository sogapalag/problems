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
    vector<int> pre(n+1, 0);
    map<int, int> las;
    for (int i = 1; i <= n; i++) {
        int x; cin >> x;
        pre[i] = las[x]; //safe way may find first, but since default zero. this way work. 
        las[x] = i;
    }
    struct Req {
        int l, r, id;
    };
    int q; cin >> q;
    vector<Req> req(q);
    for (int i = 0; i < q; i++) {
        cin >> req[i].l >> req[i].r;
        req[i].id = i;
    }
    sort(req.begin(), req.end(), [](auto& u, auto& v){
            return u.r < v.r;
            });
    Fenwick<> f(n);
    int i = 1;
    vector<int> res(q);
    for (auto& p: req) {
        while (i <= p.r) {
            f.add(i, 1);
            if (pre[i]) f.add(pre[i], -1);
            i++;
        }
        res[p.id] = f.query(p.l, p.r);
    }
    for (auto& x: res) {
        cout << x << "\n";
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
