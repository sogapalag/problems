#include <bits/stdc++.h>

using namespace std;

using ll=long long ;
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
    int n; cin >> n;
    vector<ll> s(n);
    for (int i = 0; i < n; i++) {
        cin >> s[i];
    }
    Fenwick<ll> f(n);
    Fenwick<int> st(n);
    for (int i = 1; i <= n; i++) {
        f.add(i, i);
        st.add(i, 1);
    }
    vector<int> a(n);
    for (int i = n-1; i >= 0; i--) {
        int k = bs_first<int>(0, n+1, [&](int x){
                return f.query(x) >= s[i];
                });
        int p = bs_first<int>(k+1, n+1, [&](int x){
                return st.query(k+1, x) >= 1;
                });
        a[i] = p;
        f.add(p, -p);
        st.add(p, -1);
    }
    for (auto& x: a) {
        cout << x << ' ';
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
