#include <bits/stdc++.h>

using namespace std;

template <typename T>
struct Segtree {
    int n; // leaf [n, 2n), view as original [0, n)
    int sz_v;
    const T ID;
    vector<T> v; //tree
    
    Segtree(int _n = 100005) : n(_n), sz_v(n<<1), ID() {
        v.resize(sz_v);
    }
    void init(vector<int>& raw) {// set leaf value
        for (int i = 0; i < n; i++) {
            v[i+n].emplace_back(raw[i]);
        }
        build();
    }
    void build() {
        for (int i = n-1; i >= 1; i--) {
            merge(v[i<<1].begin(), v[i<<1].end(), v[i<<1|1].begin(), v[i<<1|1].end(), back_inserter(v[i]));
        }
    }
    // cnt #<=x
    inline int query(int l, int r, int x) {
        int cnt = 0;
        for (l += n, r += n; l < r; l >>= 1, r >>= 1) {
            if (l & 1) { cnt += upper_bound(v[l].begin(), v[l].end(), x) - v[l].begin(); l++; }
            if (r & 1) { r--; cnt += upper_bound(v[r].begin(), v[r].end(), x) - v[r].begin(); }
        }
        return cnt;
    }
};

typedef Segtree<vector<int>> Seg;

const int N = 100005; 
queue<int> q[N];
void solve() {
    int n,k;
    cin >> n >> k;
    vector<int> pre(n, -1);
    for (int i = 0; i < n; i++) {
        int x; cin >> x;
        q[x].push(i);
        if (q[x].size() > k) {
            pre[i] = q[x].front(); q[x].pop();
        }
    }
    Seg seg(n); seg.init(pre);
    int res = 0;
    int q; cin >> q;
    while (q--) {
        int l,r;
        cin >> l >> r;
        l = (l+res)%n + 1;
        r = (r+res)%n + 1;
        if (l > r) swap(l, r);
        l--;
        res = seg.query(l, r, l-1);
        cout << res << '\n';
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}
