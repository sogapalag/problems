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

Fenwick<int> f[4][10][10];
void solve() {
    string s; cin >> s;
    int n = s.size();
    int mp[256];
    mp['A']=0;mp['T']=1;mp['G']=2;mp['C']=3;
    for (int i = 0; i < n; i++) {
        int x = mp[s[i]];
        for (int m = 1; m <= 10; m++) {
            f[x][m-1][i%m].add(i+1, 1);
        }
    }
    
    int q; cin >> q;
    while (q--) {
        int op; cin >> op;
        if (op == 1) {
            int i; char c;
            cin >> i >> c; i--;
            for (int m = 1; m <= 10; m++) {
                f[mp[s[i]]][m-1][i%m].add(i+1, -1);
                f[mp[c]][m-1][i%m].add(i+1, 1);
            }
            s[i] = c;
        } else {
            int l,r; string t;
            cin >> l >> r >> t;
            l--; int m = t.size();
            int res = 0;
            for (int i = 0; i < m; i++) {
                int x = mp[t[i]];
                res += f[x][m-1][(i+l)%m].query(l+1, r);
            }
            cout << res << "\n";
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}
