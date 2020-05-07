#include <bits/stdc++.h>

using namespace std;

// SNIPPETS_START seglazy_range_add_global_min
struct RangeAddGlobalMin {
    using T = long long;
    int N;
    vector<T> a, d;

    RangeAddGlobalMin(int n, T leaf_default = 0) {
        init_space(n);
        fill(a.begin() + N, a.begin() + N + n, leaf_default);
        build();
    }
    RangeAddGlobalMin(const vector<T>& leaves) {
        int n = leaves.size();
        init_space(n);
        copy(leaves.begin(), leaves.end(), a.begin() + N);
        build();
    }
    void init_space(int n) {
        N = 1; while (N < n) N <<= 1;
        a.assign(N<<1, 0x3f3f3f3f3f3f3f3f);
        d.assign(N, 0);
    }
    inline void pull(int i) {
        a[i] = min(a[i<<1], a[i<<1|1]);
    }
    void build() {
        for (int i = N-1; i >= 1; i--) pull(i);
    }
    inline void apply(int i, const T& val) {
        a[i] += val;
        if (i < N) d[i] += val;
    }
    inline void push(int i) {
        if (d[i]==0) return; // 2xfaster
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
    T get_min() const {
        return a[1];
    }
};
// SNIPPETS_END
