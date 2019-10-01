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

void solve() {
    int n,m;
    cin >> n >> m;
    vector<pair<int, int>> a(n);
    for (int i = 0; i < n; i++) {
        int x,y;
        cin >> x >> y;
        a[i] = {y-x+1, x};
    }
    sort(a.begin(), a.end());

    Fenwick<> f(m);
    int i = 0;
    for (int j = 1; j <= m; j++) {
        while (i < n && a[i].first < j) {
            int len,x;
            tie(len,x) = a[i];
            f.add(x, 1);
            f.add(x+len, -1);
            i++;
        }
        int res = n-i;
        for (int k = j; k <= m; k+=j) {
            res += f.query(k);
        }
        cout << res << "\n";
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
