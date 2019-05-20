#include <bits/stdc++.h>

using namespace std;

// when range [l, r), has property notP~P, want first P.
// when return r, means not found.
template <typename T>
T bs_fisrt(T l, T r, function<bool (T)> f) {
    assert(l < r);
    T mid;
    while (l != r) {
        mid = (l+r)/2;
        if (f(mid)) {
            r = mid;
        }else {
            l = mid + 1;
        }
    }
    return r;
}
const int A = 1e9+10; 

template <typename T=int>
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
        for (int i = n-1; i >= 0; i--) {
            merge(v[i<<1].begin(), v[i<<1].end(), v[i<<1|1].begin(), v[i<<1|1].end(), back_inserter(v[i]));
        }
    }
    // bs cnt (#<=x) >= k 
    inline int query(int _l, int _r, int k) {
        return bs_fisrt<int>(0, n, [&](int x){
                int cnt = 0;
                int l = _l, r = _r;
                for (l += n, r += n; l < r; l >>= 1, r >>= 1) {
                    if (l & 1) { cnt += upper_bound(v[l].begin(), v[l].end(), x) - v[l].begin(); l++; }
                    if (r & 1) { r--; cnt += upper_bound(v[r].begin(), v[r].end(), x) - v[r].begin(); }
                }
                return cnt >= k;
                });        
    }
};

typedef Segtree<vector<int>> Seg;

void solve() {
    int n, m;
    cin >> n >> m;
    vector<int> a(n);
    for (auto& x: a) {
        cin >> x;
    }
    // compress, constant optimization, otherwise TLE
    vector<int> b(a);
    sort(b.begin(), b.end());
    b.erase(unique(b.begin(), b.end()), b.end());
    map<int, int> map;
    for (int i = 0; i < b.size(); i++) {
        map[b[i]] = i;
    }
    for (auto& x: a) {
        x = map[x];
    }
    // merge segtree
    Seg seg(n); seg.init(a);
    while (m--) {
        int x, y, k;
        cin >> x >> y >> k;
        cout << b[seg.query(x-1, y, k)] << "\n";
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
