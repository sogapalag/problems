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

// key: hall's theorem
// to check whether at least res, let S={pos[>=res]}, T={bomb-pos}
//   it's trivial to note if S skew left, false; if S skew right true.
//   by hall's, we check suffix, since last k bomb can only delete at most k number in the suffix.
//   so let r[i] = #>=res - #bomb in suffix[i..], if some r[i] >= 1, then true;
void solve() {
    int n; cin >> n;
    vector<int> a(n), pos(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i]; --a[i];
        pos[a[i]] = i;
    }
    vector<int> b(n);
    for (auto& x: b) {
        cin >> x; x--;
    }

    RangeAddGlobalMax rmx(n);
    int res = n;
    for (int _ = 0; _ < n; _++) {
        while (rmx.get_max() < 1) {
            res--;
            rmx.add(0, pos[res] + 1, 1);
        }
        cout << res+1 << ' ';
        rmx.add(0, b[_]+1, -1);
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}
