#include <bits/stdc++.h>

using namespace std;

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
// when range [l, r), has property notP~P, want first P.
// when return r, means not found.
template <typename T>
T bs_first(T l, T r, function<bool (T)> f) {
    assert(l < r);
    T mid;
    while (l != r) {
        mid = l + (r-l)/2;
        if (f(mid)) {
            r = mid;
        }else {
            l = mid + 1;
        }
    }
    return r;
}
void solve() {
    int n,m;
    cin >> n >> m;
    swap(n,m);
    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    for (int i = n-1; i >= 1; i--) {
        a[i] -= a[i-1];
    }
    Fenwick<int> occur(m);
    vector<int> res(m + 1);
    for (int i = 1; i <= m; i++) {
        int x; cin >> x; res[i] = x;
        if (x == -1) {
            int l = 1;
            for (int z: a) {
                if (l > i || occur.query(l, i) < z) break;
                int k = bs_first<int>(l, i+1, [&](int k){
                        return occur.query(l, k) >= z;
                        });
                occur.add(k, -1);
                l = k + 1;
            }
        } else {
            occur.add(i, 1);
        }
    }
    if (occur.query(m) == 0) {
        cout << "Poor stack!"; return;
    }
    for (int i = 1; i <= m; i++) {
        if (occur.query(i,i)) cout << res[i];
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}
