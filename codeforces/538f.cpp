#include <bits/stdc++.h>

using namespace std;


void __solve() {
    int n; cin >> n;
    vector<int> a(n);
    for (auto& x: a) {
        cin >> x;
    }
    //vector<int> diff(n);
    //for (int i = 1; i < n; i++) {
    //    diff[1] += a[i-1] > a[i];
    //    for (int k = 2; k*k <= i-1; k++) {
    //        diff[k] += (a[(i-1)/k] > a[i]) - (a[(i-1)/(k-1)] > a[i]);
    //    }
    //    for (int pv = 0; pv*pv <= i-1; pv++) {
    //        int k = pv ? (i-1)/pv : i; // n-1
    //        //cerr<<k<<' '<< pv<<endl;
    //        assert((i-1)/(k+1) <= pv);
    //        while ((i-1)/(k+1) > pv) {
    //            k++;
    //        }
    //        while (k >= 2 && (i-1)/(k-1) == pv) {
    //            k--;
    //            if (k <= 1 || k*k <= i-1) break;
    //        }
    //        if (k <= 1 || k*k <= i-1) continue;
    //        diff[k] += (a[(i-1)/k] > a[i]) - (a[(i-1)/(k-1)] > a[i]);
    //    }
    //}

    // https://math.stackexchange.com/questions/422559/what-is-sum-limits-i-1n-sqrt-i
    // \sum sqrt(i) ~ 2/3 n^1.5
    vector<int> diff(n + 1);
    // pa vary sqrt
    for (int i = 1; i < n; i++) {
        int p;
        for (p = 0; p*p <= i-1; p++) {
            int kl = (i-1)/(p+1) + 1;
            int kr = p ? (i-1)/p : n-1;
            assert((i-1)/kl == p);
            assert(kl==1 || (i-1)/(kl-1) > p);
            assert((i-1)/kr == p);
            assert(kr==n-1 || (i-1)/(kr+1) < p);
            if (a[p] > a[i]) {
                diff[kl]++;
                diff[kr+1]--;
            }
        }
        for (int k = 1; k <= (i-1)/p; k++) {//<=, since p)
            int pv = (i-1)/k;
            if (a[pv] > a[i]) {
                diff[k]++;
                diff[k+1]--;
            }
        }
    }
    for (int i = 1, x = 0; i < n; i++) {
        x += diff[i];
        cout << x << ' ';
    }
}


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

void solve() {
    int n; cin >> n;
    vector<int> a(n);
    for (auto& x: a) {
        cin >> x;
    }
    Seg seg(n); seg.init(a);
    for (int k = 1; k < n; k++) {
        int res = 0;
        // only n/k has ch, 
        for (int p = 0; p*k+1 < n; p++) {
            // count ch-range < a[p]
            res += seg.query(p*k+1, min(p*k + k + 1,n), a[p] - 1);
        }
        cout << res << ' ';
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}
