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

template <typename T=int>
struct Compress {
    map<T, int> id;
    vector<T> num;

    Compress(vector<T> v) {
        sort(v.begin(), v.end());
        v.erase(unique(v.begin(), v.end()), v.end());
        num = v;
        for (int i = 0; i < (int)num.size(); i++) {
            id[num[i]] = i;
        }
    }

    inline int get_id(T x) {
        assert(id.count(x));
        return id[x];
    }
    inline T get_num(int i) {
        assert(0 <= i && i < num.size());
        return num[i];
    }
};

void solve() {
    int n, K;
    cin >> n >> K;
    vector<int> a(n);
    for (auto& x: a) {
        cin >> x;
    }
    vector<ll> f(n+1);
    f[0] = 0;
    for (int i = 1; i <= n; i++) {
        f[i] = f[i-1] + a[i-1] - K;
    }
    Compress<ll> c(f);
    Fenwick<int> st(n+3);
    ll res = 0;
    for (int i = 0; i <= n; i++) {
        int j = c.get_id(f[i]) + 1;
        res += st.query(j);
        st.add(j, 1);
    }
    cout << res;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
