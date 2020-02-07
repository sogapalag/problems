#include <bits/stdc++.h>

using namespace std;
using ll=long long;
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
// when range [l, r), has property P~notP, want last P.
// when return l-1, means not found.
template <typename T>
T bs_last(T l, T r, function<bool (T)> f) {
    assert(l < r);
    T mid;
    while (l != r) {
        mid = l + (r-l)/2;
        if (f(mid)) {
            l = mid + 1;
        }else {
            r = mid;
        }
    }
    return r-1;
}
void solve() {
    int n, m; ll T;
    cin >> n >> m >> T;
    vector<int> a(n);
    for (auto& x: a) {
        cin >> x;
    }
    vector<int> id(n);
    iota(id.begin(), id.end(), 0);
    sort(id.begin(), id.end(), [&](auto& u, auto& v){
        return a[u] < a[v];
    });
    Fenwick<int> occur(n);
    Fenwick<ll> sum(n);

    auto cost = [&](int k){
        int i = occur.query(k);
        if (!i) return 0ll;
        ll base = sum.query(k);
        //cerr<<i<<' '<<k<<endl;
        if (i > m) {
            int ta = (i-1)/m*m;
            i = bs_last<int>(1, k, [&](int i){
                    return occur.query(i) <= ta;
                    });
            base += sum.query(i);
        }
        return base;
    };
    auto ck = [&](int k){
        return cost(k) <= T;
    };
    int res = 0, d = 1;
    int _=0;
    // a brute force for each x. there should be ternary, omit
    while (_ < n && a[id[_]] <= T) {
        int j = _;
        while (j < n && a[id[j]] == a[id[_]]) {
            occur.add(id[j] + 1, 1);
            sum.add(id[j] + 1, a[id[j]]);
            j++;
        }
        int k = bs_last<int>(1, n+1, ck);
        k = occur.query(k);
        if (k > res) {
            res = k;
            d = a[id[_]];
        }
        _ = j;
    }
    cout << res << ' ' << d << '\n';
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int T; cin >> T;
    for (int t = 0; t < T; t++) {
        solve();
    }
    return 0;
}
