#include <bits/stdc++.h>

using namespace std;

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

    int find(T x, int i, int sl, int sr) {
        if (sr - sl == 1) {
            return i-N + (a[i]<x);
        }
        int sm = (sl+sr)>>1, il = i<<1, ir = i<<1|1;
        push(i);
        if (a[ir] < x) return find(x, ir, sm, sr);
        return find(x, il, sl, sm);
    }
    // find ret := #strictly less than x
    // i < ret <=> val[i] < x
    int find(T x) {
        return find(x, 1, 0, N);
    }
    void push_all() {
        for (int i = 1; i < N; i++) {
            push(i);
        }
    }
    T get(int i) { return a[i+N]; }
};
using ll=long long;

// note by time reversal, (l,r) down event like
//  if l < x then r += y. or r < x, l += y. i.e. partial 1-dim result the other dim inc.
// wlog, below L'/': 0 , 1..., n-1
//             R'\': n-1,...1, 0
// the key is the whole time, L,R are always monotonic, so we can bs which partial should update.
// caution: r += 2*y,(draw 2x2 square line, notice parity..) and final depth y /= 2.
void solve() {
    int n, q;
    cin >> n >> q;
    vector<tuple<int,int,int>> qrs(q);
    for (int i = 0; i < q; i++) {
        int x,op,y;
        cin >> x >> op >> y;
        qrs[i] = make_tuple(op,x,y);
    }
    vector<ll> a(n);
    iota(a.begin(), a.end(), 0);
    RangeAddGlobalMin L(a), R(a);
    for (int _ = q-1; _ >= 0; _--) {
        int op,x,y;
        tie(op,x,y) = qrs[_];
        //x = max(0, min(n, x));
        if (op == 1) {
            x = L.find(x);
            R.add(n-x, n, y * 2); // *2....
        } else {
            x = n-x;
            x = R.find(x);
            L.add(n-x, n, y * 2);
        }
        //cerr<<x<<endl;
    }
    L.push_all();
    R.push_all();
    for (int i = 0; i < n; i++) {
        ll y = L.get(i) + R.get(n-i-1);
        y -= n-1;
        y /= 2; // /2
        cout << y << '\n';
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}
