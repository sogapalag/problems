#include <bits/stdc++.h>

using namespace std;
using ll=long long;
const ll NINF = 0xc0c0c0c0c0c0c0c0;

struct RangeAddGlobalMax {
    using T = ll;
    int N;
    vector<T> a, d;

    RangeAddGlobalMax(int n, T leaf_default = 0) {
        init_space(n);
        fill(a.begin() + N, a.begin() + N + n, leaf_default);
        build();
    }
    RangeAddGlobalMax(const vector<T>& leaves) {
        int n = leaves.size();
        init_space(n);
        copy(leaves.begin(), leaves.end(), a.begin() + N);
        build();
    }
    void init_space(int n) {
        N = 1; while (N < n) N <<= 1;
        a.assign(N<<1, NINF);
        d.assign(N, 0);
    }
    inline void pull(int i) {
        a[i] = max(a[i<<1], a[i<<1|1]);
    }
    void build() {
        for (int i = N-1; i >= 1; i--) pull(i);
    }
    inline void apply(int i, const T& val) {
        a[i] += val;
        if (i < N) d[i] += val;
    }
    inline void push(int i) {
        apply(i<<1, d[i]);
        apply(i<<1|1, d[i]);
        d[i] = 0;
    }
    void add(int l, int r, const T& val, int i, int sl, int sr) {
        if (r <= sl || sr <= l) return;
        if (l <= sl && sr <= r) return apply(i, val);
        int sm = (sl+sr)>>1, il = i<<1, ir = i<<1|1;
        push(i);
        add(l, r, val, il, sl, sm);
        add(l, r, val, ir, sm, sr);
        pull(i);
    }

    void add(int l, int r, const T& val) {
        add(l, r, val, 1, 0, N);
    }
    T get_max() const {
        return a[1];
    }
};
const int N = 1e6+10; 
void solve() {
    int n,m,p;
    cin >> n >> m >> p;
    vector<ll> aset(N, NINF);
    for (int i = 0; i < n; i++) {
        int x,y;
        cin >> x >> y;
        aset[x] = max(aset[x], (ll)-y);
    }
    vector<ll> best(N, NINF);
    for (int i = 0; i < m; i++) {
        int x,y;
        cin >> x >> y;
        best[x] = max(best[x], (ll)-y);
    }
    RangeAddGlobalMax s(best);
    vector<vector<pair<int,int>>> evs(N);
    for (int _ = 0; _ < p; _++) {
        int x,y,z;
        cin >> x >> y >> z;
        evs[x].emplace_back(y, z);
    }
    ll res = NINF;
    // note profit is 2d prefix
    // we iter x
    for (int i = 1; i < N; i++) {
        res = max(res, s.get_max() + aset[i]);
        for (auto& _: evs[i]) {
            int y,z;
            tie(y,z) = _;
            // those y can has the profit
            s.add(y+1, N, z);
        }
    }
    cout << res;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}
