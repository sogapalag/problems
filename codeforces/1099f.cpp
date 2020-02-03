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
// when range [l, r), has property P~notP, want last P.
// when return l-1, means not found.
template <typename T>
T bs_last(T l, T r, function<bool (T)> f) {
    assert(l < r);
    T mid;
    while (l != r) {
        mid = l + (r-l)/2;
        if (f(mid)) {
            l = mid + 1;
        }else {
            r = mid;
        }
    }
    return r-1;
}
using ll=long long;
void solve() {
    int n; ll T;
    cin >> n >> T;
    vector<int> a(n), t(n);
    for (auto& x: a) {
        cin >> x;
    }
    for (auto& x: t) {
        cin >> x;
    }
    vector<int> pa(n), l(n);pa[0]=-1;
    vector<vector<int>> g(n);
    for (int i = 1; i < n; i++) {
        int p,x;
        cin >> p >> x;
        p--;
        pa[i] = p;
        g[p].push_back(i);
        l[i] = x;
    }

    const int N = 1e6+10; 
    const int M = 1e6; 
    Fenwick<ll> cum(N), occur(N);
    vector<ll> dp(n);
    function<void(int)> dfs = [&](int u){
        cum.add(t[u], t[u]*1ll*a[u]);
        occur.add(t[u], a[u]);
        int i = bs_last<int>(1, N, [&](int i){
                return cum.query(i) <= T;
                });
        dp[u] = occur.query(i);
        // \E a bunch next
        if(i<M)dp[u] += (T - cum.query(i))/(i+1);
        // two max sub
        ll mx[2]={};
        for (int v: g[u]) {
            T -= 2*l[v];
            dfs(v);
            if (dp[v] >= mx[1]) mx[1] = dp[v];
            if (mx[1] > mx[0]) swap(mx[0], mx[1]);
            T += 2*l[v];
        }
        if (u == 0) {//first step cannot forbid
            dp[u] = max(dp[u], mx[0]);
        } else {//can use second
            dp[u] = max(dp[u], mx[1]);
        }
        cum.add(t[u], -t[u]*1ll*a[u]);
        occur.add(t[u], -a[u]);
    };
    dfs(0);
    cout << dp[0];
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}
