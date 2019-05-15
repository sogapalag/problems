#include <bits/stdc++.h>

using namespace std;

template <typename T=int>
struct Fenwick {
    int n;
    vector<T> v;
    
    Fenwick(int size = 100005) : n(size+1), v(n, 0) {}
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
const int N = 1e7+111; 

void solve() {
    int T; cin >> T;
    while (T--) {
        int n; cin >> n;
        Fenwick<> fen(N);
        long long res = 0;
        for (int i = 0; i < n; i++) {
            int x; cin >> x;
            res += fen.query(x+1, N);
            fen.add(x, 1);
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
