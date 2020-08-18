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

// when range [l, r), has property notP~P, want first P.
// when return r, means not found.
template <typename T>
T bs_first(T l, T r, function<bool (T)> f) {
    assert(l < r);
    T mid;
    while (l != r) {
        mid = l + (r-l)/2;
        if (f(mid)) {
            r = mid;
        }else {
            l = mid + 1;
        }
    }
    return r;
}

// iter #11, key ds: query k-least-sum, 2BIT, or segtree or treap(TODO? friendly usable ds)
void solve() {
    int n,m,k;
    cin >> n >> m >> k;
    vector<int> a(n);
    vector<int> g[2][2];
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        int x,y;
        cin >> x >> y;
        g[x][y].push_back(i);
    }
    int lb,ub;
    {
        int c = min(g[0][1].size(), g[1][0].size());
        lb = max({0, k-c, 2*k-m});
        ub = min(k, (int)g[1][1].size());
    }
    if (lb > ub) {
        cout << -1; return;
    }
    auto comp = [&](int u, int v){
        return a[u] < a[v];
    };
    vector<int> id(n);
    iota(id.begin(), id.end(), 0);
    sort(id.begin(), id.end(), comp);
    for (int x = 0; x < 2; x++) {
        for (int y = 0; y < 2; y++) {
            sort(g[x][y].begin(), g[x][y].end(), comp);
        }
    }
    vector<int> pos(n);
    Fenwick<int> sum(n), sz(n);
    for (int i = 0; i < n; i++) {
        sz.add(i+1, 1);
        sum.add(i+1, a[id[i]]);
        pos[id[i]] = i;
    }
    int must = 0;
    auto add = [&](int i){
        sz.add(pos[i]+1, 1);
        sum.add(pos[i]+1, a[i]);
        must -= a[i];
    };
    auto del = [&](int i){
        sz.add(pos[i]+1, -1);
        sum.add(pos[i]+1, -a[i]);
        must += a[i];
    };
    for (int x = 0; x < lb; x++) {
        int i = g[1][1][x];
        del(i);
    }
    for (int y = 0; y < k-lb; y++) {
        int i = g[0][1][y];
        del(i);
        i = g[1][0][y];
        del(i);
    }
    int mi = 2e9+10, z = -1;
    for (int x = lb; x <= ub; x++) {
        int need = m - x - 2*(k-x);
        int p = bs_first<int>(0, n+1, [&](int p){
                return sz.query(p) >= need;
                });
        int tmp = must + sum.query(p);
        if (tmp < mi) {
            mi = tmp; z = x;
        }
        if (x == ub) break;
        int i = g[1][1][x];
        del(i);
        i = g[0][1][k-x-1];
        add(i);
        i = g[1][0][k-x-1];
        add(i);
    }
    assert(z != -1);
    vector<bool> trk(n);
    vector<int> res;
    for (int x = 0; x < z; x++) {
        int i = g[1][1][x];
        res.push_back(i);
        trk[i] = true;
    }
    for (int y = 0; y < k-z; y++) {
        int i = g[0][1][y];
        res.push_back(i);
        trk[i] = true;

        i = g[1][0][y];
        res.push_back(i);
        trk[i] = true;
    }
    for (int i:id)if(!trk[i] && (int)res.size() < m) {
        res.push_back(i); trk[i] = true;
    }
    int ans = 0;
    for (int i:res) ans += a[i];
    assert(ans == mi);
    cout << ans << "\n";
    for (int i:res) cout << i+1 << ' ';
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}
