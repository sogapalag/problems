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
    Fenwick<int> f;
    for (int i = 0; i < n; i++) {
        int x; cin >> x;
        int len = f.query(x-1) + 1;
        f.add(x, len);
    }
    cout << f.query(100'002);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
