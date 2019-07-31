#include <bits/stdc++.h>

using namespace std;

template <typename T=int>
struct Fenwick {
    int n;
    vector<T> v;
    
    Fenwick(int size = 100005) : n(size), v(n+1, 0) {}
    inline void add(int p, T val) {
        for (; p <= n; p += (p&-p)) { v[p] = max(v[p], val); }
    }
    inline T query(int p) {
        T tmp = 0;
        for (; p > 0; p -= (p&-p)) { tmp = max(tmp, v[p]); }
        return tmp;
    }
};

void solve() {
    int n; cin >> n;
    vector<int> a(n);
    for (auto& x: a) {
        cin >> x;
    }
    int q; cin >> q;
    vector<int> las(n, q+1);
    Fenwick<int> suf(q);
    for (int i = q; i >= 1; i--) {
        int op; cin >> op;
        if (op == 1) {
            int p, x;
            cin >> p >> x;
            p--;
            las[p] = i;
            a[p] = x;
        } else {
            int x; cin >> x;
            suf.add(i, x);
        }
    }

    for (int i = 0; i < n; i++) {
        int tmp = suf.query(las[i]-1);
        int res = max(a[i], tmp);
        cout << res << ' ';
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
