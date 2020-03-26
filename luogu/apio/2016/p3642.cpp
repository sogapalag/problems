#include <bits/stdc++.h>

using namespace std;

using ll=long long;

struct MidPoint {
    priority_queue<ll> L;
    priority_queue<ll,vector<ll>,greater<ll>> R;
    ll res = 0;

    void LtoR() {
        res += L.top(); R.push(L.top());
        res += L.top(); L.pop();
    }
    void RtoL() {
        res -= R.top(); L.push(R.top());
        res -= R.top(); R.pop();
    }
    void push(ll x) {
        if (L.empty() || x >= L.top()) {
            R.push(x); res += x;
        } else {
            LtoR();
            L.push(x); res -= x;
        }
        while (L.size() < R.size()) {
            RtoL();
        }
    }
};

// slightly WRONG
// each subtree, slope -1,0,1, i.e. \_/ shape
// thus trk l,r. and when merge, since \_/ is {|x-l|+|x-r| - (r-l)}/2
//  so maintain MidPoint
// WRONG cause we cannot always pick optimal since w cannot dec to negative
void __solve() {
    int n,m;
    cin >> n >> m;
    n += m;
    vector<vector<int>> g(n);
    vector<int> w(n);
    for (int i = 1; i < n; i++) {
        int p,x;
        cin >> p >> x;
        p--;
        g[p].push_back(i);
        w[i] = x;
    }
    vector<ll> dp(n);
    vector<ll> l(n), r(n);
    function<void(int)> dfs = [&](int u){
        if (u >= n-m) return;
        MidPoint mid;
        for (int v:g[u]){
            dfs(v);
            l[v] += w[v];
            r[v] += w[v];
            mid.push(l[v]);
            mid.push(r[v]);
            dp[u] -= r[v] - l[v];
            dp[u] += 2*dp[v];
        }
        dp[u] += mid.res;
        dp[u] /= 2;
        l[u] = mid.L.top();
        r[u] = mid.R.top();
    };
    dfs(0);
    cout << dp[0];
}

// each sub form should be -k,...,-1,0,1
// when +w, top-two shift
// when merge, note each cut still be cut
//  and since we know the form, we pop out slope > 1
// and since we know f(0)=total w, and know the cut.
//  thus f(L) = f(0) - sum(cut)
void solve() {
    int n,m;
    cin >> n >> m;
    n += m;
    vector<vector<int>> g(n);
    vector<int> w(n);
    ll res = 0;
    for (int i = 1; i < n; i++) {
        int p,x;
        cin >> p >> x;
        p--;
        g[p].push_back(i);
        w[i] = x;
        res += x;
    }
    vector<int> sz(n, 1);
    vector<priority_queue<ll>> cut(n);
    function<void(int)> dfs = [&](int u){
        if (u >= n-m) {
            cut[u].push(0);
            cut[u].push(0);
            return;
        }
        for (int& v:g[u]){
            dfs(v);
            if (sz[v] > sz[g[u][0]]) swap(v, g[u][0]);
            sz[u] += sz[v];
        }
        for (int v:g[u]) {
            if (v==g[u][0]) {
                ll r = cut[v].top(); cut[v].pop();
                ll l = cut[v].top(); cut[v].pop();
                cut[u] = move(cut[v]);
                cut[u].push(l+w[v]);
                cut[u].push(r+w[v]);
            } else {
                ll r = cut[v].top(); cut[v].pop();
                ll l = cut[v].top(); cut[v].pop();
                cut[u].push(l+w[v]);
                cut[u].push(r+w[v]);
                while(cut[v].size()) {
                    cut[u].push(cut[v].top());
                    cut[v].pop();
                }
            }
        }
        for (int _ = g[u].size(); _ > 1; _--) {
            cut[u].pop();
        }
    };
    dfs(0);
    cut[0].pop();
    while (cut[0].size()) {
        res -= cut[0].top(); cut[0].pop();
    }
    cout << res;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}
