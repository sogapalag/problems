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
const int N = 1e6+10; 
void solve() {
    int n,q;
    cin >> n >> q;
    vector<vector<int>> evs(N);
    for (int _ = 0; _ < n; _++) {
        int x,y;
        cin >> x >> y; y++;
        evs[y].push_back(x);
    }
    vector<vector<int>> qrs(N);
    vector<int> las(q);
    for (int i = 0; i < q; i++) {
        int m; cin >> m;
        for (int _ = 0; _ < m; _++) {
            int x; cin >> x;
            qrs[x].push_back(i);
        }
        qrs[N-1].push_back(i);
    }
    
    // offline, exclude
    Fenwick<int> occur(N);
    vector<int> res(q);
    for (int r = 1; r < N; r++) {
        for (int l: evs[r]) {
            occur.add(l, 1);
        }
        for (int i: qrs[r]) {
            int l = las[i];
            if (l+1 <= r-1) res[i] += occur.query(l+1, r-1);
            las[i] = r;
        }
    }
    for (auto& x: res) {
        cout << n-x << '\n';
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}
