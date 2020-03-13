#include <bits/stdc++.h>

using namespace std;

struct Dinic {
    using F = int; const static F INF = 0x3f3f3f3f; 
    //using F = long long; const static F INF = 0x3f3f3f3f3f3f3f3f; 
    struct Edge {
        int v, bro; F cap;
        Edge() {}
        Edge(int _v, int _bro, F _cap) : v(_v), bro(_bro), cap(_cap) {}
    };
    vector<Edge> e;
    vector<int> pos, cur;
    int n, s, t, m;
    Dinic(int _n, int _s, int _t) : n(_n), s(_s), t(_t), m(0) {
        pos.assign(n, -1);
        cur.resize(n);
        d.resize(n);
        e.reserve(4e5);
    }
    void add(int u, int v, F c=INF) {
        assert(u < n && v < n);
        e.emplace_back(v, pos[u], c); pos[u] = m++;
        e.emplace_back(u, pos[v], 0); pos[v] = m++;
    }
    vector<int> d;
    // build layer graph
    bool bfs() {
        fill(d.begin(), d.end(), -1);
        d[s] = 0;
        queue<int> q; q.push(s);
        while (!q.empty()) {
            int u = q.front(); q.pop();
            for (int i = cur[u] = pos[u]; i != -1; i = e[i].bro) {
                int v = e[i].v;
                if (d[v] == -1 && e[i].cap != 0) {
                    d[v] = d[u] + 1;
                    q.push(v);
                }
            }
        }
        return d[t] != -1;
    }
    // find blocking flow
    F dfs(int u, F lim) {
        if (u == t) return lim;
        F tot = 0;
        for (int& i = cur[u]; i != -1; i = e[i].bro) {
            int v = e[i].v;
            if (e[i].cap != 0 && d[v] == d[u] + 1) {
                F flow = dfs(v, min(e[i].cap, lim-tot));
                tot += flow;
                e[i].cap -= flow;
                e[i^1].cap += flow;
                if (tot == lim) return lim;
            }
        }
        return tot;
    }
    F flow() {
        F res = 0;
        while (bfs()) {
            res += dfs(s, INF);
        }
        return res;
    }
};

// 网络流24题 最长不下降子序列问题
void solve() {
    int n; cin >> n;
    vector<int> a(n);
    for (auto& x: a) {
        cin >> x;
    }
    vector<int> len(n);
    {   
        vector<int> dp(n + 1, 2e9);
        dp[0] = 0;
        for (int i = 0; i < n; i++) {
            int k = upper_bound(dp.begin(), dp.end(), a[i]) - dp.begin();
            len[i] = k;
            dp[k] = a[i];
        }
    }
    int mx = *max_element(len.begin(), len.end());
    cout << mx << "\n";
    if (mx == 1) {
        cout << n << "\n";
        cout << n << "\n";
        return;
    }

    // most online solution use 2*n bip, i.e. add i <- i+n
    // actually n is sufficient
    int S = n, T = n + 1;
    Dinic mf(T+1, S, T);
    for (int i = 0; i < n; i++) {
        if (len[i] == 1) mf.add(S, i, 1);
        if (len[i] == mx)mf.add(i, T, 1);
        // a, len. ensure each |seq|=mx
        for (int j = 0; j < i; j++) {
            if (a[j] <= a[i] && len[j]+1 == len[i]) {
                mf.add(j, i, 1);
            }
        }
    }
    int res = mf.flow();
    cout << res << "\n";
    mf.add(S, 0, Dinic::INF);
    if (len[n-1] == mx) mf.add(n-1, T, Dinic::INF);
    res += mf.flow();
    cout << res << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}
