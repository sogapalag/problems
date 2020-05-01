#include <bits/stdc++.h>

using namespace std;

#define l first
#define r second
void __solve() {
    int n; cin >> n;
    vector<pair<int, int>> a(n);
    for (auto& x: a) {
        cin >> x.l >> x.r;
        --x.l;--x.r;
    }
    vector<int> id(n);
    iota(id.begin(), id.end(), 0);
    sort(id.begin(), id.end(), [&](auto& u, auto& v){
        return a[u] < a[v];
    });
    auto p = id;
    auto f = [&](auto perm){
        vector<int> res(n);
        for (int i = 0; i < n; i++) {
            res[perm[i]] = i;
        }
        return res;
    };
    auto pr = [&](auto perm){
        for (auto& x: perm) {
            cout << x+1 << ' ';
        }cout << '\n';
    };
    for (int _ = 1; _ < n; _++) {
        int i = id[_-1], j = id[_];
        if (a[i].l <= _ && _ <= a[i].r
                && a[j].l <= _-1 && _-1 <= a[j].r) {
            cout << "NO\n";
            pr(f(p));
            swap(p[_-1], p[_]);
            pr(f(p)); return;
        }
    }
    cout << "YES\n";
    pr(f(p));
}

template <typename T=int>
struct Rmq {
    vector<T> a;
    int n, L;
    vector<vector<int>> st;
    Rmq(vector<T> _a) : a(_a) { // pass in vec[0, n)
        n = a.size();
        build();
    }
    inline int comp(int x, int y) { // DO! > max
        return a[x] < a[y] ? x : y;
    }
    void build() {
        L = 32 - __builtin_clz(n);
        st.resize(L);
        for (int j = 0; j < L; j++) {
            st[j].resize(n);
        }
        for (int i = 0; i < n; i++) {
            st[0][i] = i;
        }
        for (int j = 1; j < L; j++) {
            for (int i = 0; i + (1<<j) <= n; i++) {
                st[j][i] = comp(st[j-1][i], st[j-1][i + (1<<(j-1))]);
            }
        }
    }
    // [l, r)
    inline int query_id(int l, int r) {
        assert(0 <= l && l < r && r <= n);
        int j = 31 - __builtin_clz(r - l);
        return comp(st[j][l], st[j][r - (1<<j)]);
    }
    inline T query(int l, int r) {
        return a[query_id(l, r)];
    }
};

// note greedy sweep must be a valid. i.e. pick min(r)
// WA //then if not unique, must exist a swap-adj
// for each x find if exist y(>x) s.t. li <= y <= ri, lj <= x <= rj
//   =>   x < y <= ri,  lj <= x
// so rmi(left[x]), check lj(y)<=x or not
void solve() {
    int n; cin >> n;
    vector<pair<int, int>> a(n);
    for (auto& x: a) {
        cin >> x.l >> x.r;
        --x.l;--x.r;
    }
    vector<vector<pair<int,int>>> g(n);
    for (int i = 0; i < n; i++) {
        g[a[i].l].emplace_back(a[i].r, i);
    }
    priority_queue<pair<int,int>, vector<pair<int,int>>, greater<pair<int,int>>> hp;
    vector<int> p(n);
    for (int i = 0; i < n; i++) {
        for (auto& _: g[i]) {
            hp.push(_);
        }
        p[i] = hp.top().second; hp.pop();
    }
    auto f = [&](auto perm){
        vector<int> res(n);
        for (int i = 0; i < n; i++) {
            res[perm[i]] = i;
        }
        return res;
    };
    auto pr = [&](auto perm){
        for (auto& x: perm) {
            cout << x+1 << ' ';
        }cout << '\n';
    };
    // WA
    // 3
    // 1 3
    // 2 2
    // 1 3
    //for (int _ = 1; _ < n; _++) {
    //    int i = p[_-1], j = p[_];
    //    if (a[i].l <= _ && _ <= a[i].r
    //            && a[j].l <= _-1 && _-1 <= a[j].r) {
    //        cout << "NO\n";
    //        pr(f(p));
    //        swap(p[_-1], p[_]);
    //        pr(f(p)); return;
    //    }
    //}

    vector<int> left(n);
    for (int x = 0; x < n; x++) {
        left[x] = a[p[x]].l;
    }
    Rmq<> rmi(left);
    for (int x = 0; x < n-1; x++) {
        int i = p[x];
        if (x<a[i].r && rmi.query(x+1, a[i].r+1) <= x) {
            cout << "NO\n";
            pr(f(p));
            swap(p[x], p[ rmi.query_id(x+1, a[i].r+1) ]);
            pr(f(p)); return;
        }
    }
    cout << "YES\n";
    pr(f(p));
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}
