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
using Freq = array<int,26>;

void solve() {
    int n; cin >> n;
    string s,t;
    cin >> s >> t;
    Freq cnt[2] = {};
    for(char c: s) cnt[0][c-'a']++;
    for(char c: t) cnt[1][c-'a']++;
    if (cnt[0] != cnt[1]) {
        cout << "NO\n"; return;
    }
    // any parity is possible, dummy swap
    for (int i = 0; i < 26; i++) {
        if (cnt[0][i] >= 2) {
            cout << "YES\n"; return;
        }
    }
    // check inversion parity
    Fenwick<> f(26), g(26);
    long long inv = 0;
    for (int i = 0; i < n; i++) {
        int x = s[i] - 'a';
        inv += f.query(x); f.add(x+1, 1);
        x = t[i] - 'a';
        inv -= g.query(x); g.add(x+1, 1);
    }
    cout << ((inv&1)? "NO\n": "YES\n");
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int t; cin >> t;
    while(t--)solve();
    cout << endl;
}
