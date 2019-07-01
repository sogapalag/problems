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
   // inline T query(int l, int r) {
   //     return query(r) - query(l-1);
   // }
};
using Fen=Fenwick<int>;

// consider tc
// 3 2 1
// 1 3 2
// the way cut b into inc-block is wrong.
// below use pref-max. ensure <=a[i]'s poss <= pos[i]
void solve() {
    int n; cin >> n;
    vector<int> a(n+1);
    vector<int> b(n+1);
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    vector<vector<int>> v(n+1);
    for (int i = 1; i <= n; i++) {
        cin >> b[i];
        v[b[i]].emplace_back(i);
    }
    for (int i = 1; i <= n; i++) {
        reverse(v[i].begin(), v[i].end());
    }
    vector<int> pos(n+1);
    for (int i = 1; i <= n; i++) {
        if (v[a[i]].empty()) {
            cout << "NO" << "\n";
            return;
        }
        pos[i] = v[a[i]].back();
        v[a[i]].pop_back();
    }
    Fen f(n);
    for (int i = 1; i <= n; i++) {
        if (f.query(a[i]) > pos[i]) {
            cout << "NO" << "\n";
            return;
        }
        f.add(a[i], pos[i]);
    }
    cout << "YES" << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int t; cin >> t;
    while (t--)solve();
    cout << endl;
}
