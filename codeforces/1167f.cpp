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

const int MOD = 1e9+7; 

const int N = 5e5+111; 

void solve() {
    int n; cin >> n;
    vector<int> a(n);
    for (auto& x: a) {
        cin >> x;
    }
    vector<int> id(n);
    iota(id.begin(), id.end(), 0);
    sort(id.begin(), id.end(), [&](int x, int y){
            return a[x] < a[y];
            });
    vector<int> map(n);
    for (int i = 0; i < n; i++) {
        map[id[i]] = i;
    }
    vector<long long> L(n);
    Fenwick<long long> fen(N);
    for (int i = 0; i < n; i++) {
        int t = map[i];
        L[i] = fen.query(t);
        fen.add(t+1, i+1);
    }
    vector<long long> R(n);
    Fenwick<long long> f3n(N);
    for (int i = n-1; i >= 0; i--) {
        int t = map[i];
        R[i] = f3n.query(t);
        f3n.add(t+1, n-i);
    }
    long long res = 0;
    for (int i= 0; i < n; i++) {
        long long tmp = (i+1ll) * (n-i) % MOD;
        tmp += L[i]%MOD * (n-i)% MOD;
        tmp += R[i]%MOD * (i+1)%MOD;
        res += tmp * a[i] % MOD;
        res %= MOD;
    }
    cout << res;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
