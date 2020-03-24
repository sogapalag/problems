#include <bits/stdc++.h>

using namespace std;

struct RangeAddGlobalMax {
    using T = int;
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
        a.assign(N<<1, 0xafafafaf);
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
// key: if some optim use len l,r, then all l<x<r can add for check whether cover>=m (since we can always feasibly delete some)
//   thus two-pointer
void solve() {
    int n,m;
    cin >> n >> m;
    vector<pair<int, int>> a(n);
    vector<int> Xs;
    for (auto& _: a) {
        int x,y;
        cin >> x >> y;
        y++;
        _ = {x,y};
        Xs.push_back(x);
        Xs.push_back(y);
    }
    sort(Xs.begin(), Xs.end());
    Xs.erase(unique(Xs.begin(), Xs.end()), Xs.end());
    auto norm = [&](int x){
        return lower_bound(Xs.begin(), Xs.end(), x) - Xs.begin();
    };
    auto len = [](auto& p){
        return p.second - p.first;
    };
    sort(a.begin(), a.end(), [&](auto& u, auto& v){
        return len(u) < len(v);
    });
    RangeAddGlobalMax cover(Xs.size());
    int res = 2e9;
    for (int l = 0, r = 0; l < n; l++) {
        while (r < n && cover.get_max() < m) {
            int x,y;
            tie(x,y) = a[r++];
            cover.add(norm(x), norm(y), 1);
        }
        if (cover.get_max() < m) break;
        res = min(res, len(a[r-1]) - len(a[l]));
        int x,y;
        tie(x,y) = a[l];
        cover.add(norm(x), norm(y), -1);
    }
    if (res > 1e9) res = -1;
    cout << res;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}
