#include <bits/stdc++.h>

using namespace std;
using ll=long long;

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
        a.assign(N<<1, 0xc0c0c0c0c0c0c0c0);
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

// much faster & elegant, but might hard to understand;
// let dp[r] be answer consider 0..r roads.
// transition is if we use road l..r, i.e. dp[r] = max_l dp[l] - sum[l..r] + profit[l..r]
//   thus rmx[l] maintain rhs
// for a plan, it should include in 0..l, since the transition must use road l..r
void solve() {
    int n, m;
    cin >> n >> m;
    vector<int> a(n);
    for (auto& x: a) {
        cin >> x;
    }
    vector<vector<pair<int,int>>> evs(n + 1);
    for (int _ = 0; _ < m; _++) {
        int l,r,x;
        cin >> l >> r >> x;
        l--;
        evs[r].emplace_back(l, x);
    }
    RangeAddGlobalMax rmx(n + 1);
    ll dp = 0;
    for (int r = 1; r <= n; r++) {
        rmx.add(0, r, -a[r-1]);
        for (auto& _: evs[r]) {
            int l,x;
            tie(l,x) = _;
            rmx.add(0, l+1, x);
        }
        dp = max(dp, rmx.get_max());
        rmx.add(r, r+1, dp);
    }
    cout << dp;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}
