#include <bits/stdc++.h>

using namespace std;

#define __up_loop(f) \
    for (int n = f.size(), i = 1; i < n; i++)\
        for (int j = i; (j += i) < n;)
#define __dn_loop(f) \
    for (int n = f.size(), i = n-1; i >= 1; i--)\
        for (int j = i; (j += i) < n;)

template <typename T>
inline void zeta(vector<T>& f) {
    __dn_loop(f) f[j] += f[i];
}
template <typename T>
inline void mobius(vector<T>& F) {
    __up_loop(F) F[j] -= F[i];
}
template <typename T>
inline void zeta_p(vector<T>& f) {
    __up_loop(f) f[i] += f[j];
}
template <typename T>
inline void mobius_p(vector<T>& F) {
    __dn_loop(F) F[i] -= F[j];
}

const int N = 2e5+10; 
vector<int> ds[N];
void prep() {
    for (int i = 1; i < N; i++) {
        for (int j = i; j < N; j+=i) {
            ds[j].push_back(i);
        }
    }
}

using ll=long long;

// there is dsu method. omit
void solve() {
    prep();
    int n; cin >> n;
    vector<int> a(n);
    for (auto& x: a) {
        cin >> x;
    }
    vector<vector<int>> g(n);
    for (int _ = 1; _ < n; _++) {
        int x,y;
        cin >> x >> y;
        x--;y--;
        g[x].push_back(y);
        g[y].push_back(x);
    }

    vector<vector<int>> cnt(n);
    vector<ll> F(N);
    vector<int> dp(N);
    function<void(int,int)> dfs = [&](int u, int p){
        // must dfs all first, since we use rep dp(map)
        for (int v:g[u])if(v!=p) dfs(v,u);
        for (int d:ds[a[u]]) dp[d] = 1;
        for (int v:g[u])if(v!=p){
            // convo
            for (int _ = 0; _ < cnt[v].size(); _++) {
                int d = ds[a[v]][_];
                if (a[u] % d == 0) {
                    F[d] += 1ll * dp[d] * cnt[v][_];
                    dp[d] += cnt[v][_];
                }
            }
        }
        // put dp into cnt. clear dp(map)
        for (int d: ds[a[u]]) {
            cnt[u].push_back(dp[d]);
            dp[d] = 0;
        }
    };
    dfs(0, -1);
    mobius_p(F);
    for (auto& x: a) {
        F[x]++;
    }
    for (int i = 1; i <= 200000; i++) {
        if (F[i]) {
            cout << i << ' ' << F[i] << "\n";
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}
