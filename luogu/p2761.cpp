#include <bits/stdc++.h>

using namespace std;
using ll=long long;
using pi=pair<ll,int>;

// 网络流24题 软件补丁问题
// dijkstra
void solve() {
    int n,m;
    cin >> n >> m;
    const int MSK = 1<<n; 
    vector<int> cost(m), b1(m), b2(m, MSK-1), f1(m, MSK-1), f2(m);
    for (int i = 0; i < m; i++) {
        cin >> cost[i];
        {
            string s; cin >> s;
            for (int j = 0; j < n; j++) {
                if (s[j]=='+')b1[i] ^= 1<<j;
                if (s[j]=='-')b2[i] ^= 1<<j;
            }
        }
        {
            string s; cin >> s;
            for (int j = 0; j < n; j++) {
                if (s[j]=='-')f1[i] ^= 1<<j;
                if (s[j]=='+')f2[i] ^= 1<<j;
            }
        }
    }

    vector<ll> d(MSK, 1ll<<60);
    vector<bool> trk(MSK);
    d[MSK-1] = 0;
    priority_queue<pi,vector<pi>,greater<pi>> pq;    
    pq.emplace(0, MSK-1);
    while (!pq.empty()) {
        ll x; int u;
        tie(x,u) = pq.top(); pq.pop();
        if (trk[u]) continue;
        trk[u] = true;
        for (int i = 0; i < m; i++) {
            if ((b1[i]&u) != b1[i]) continue;
            if ((b2[i]|u) != b2[i]) continue;
            int v = (u&f1[i])|f2[i];
            if (d[v] > d[u] + cost[i]) {
                d[v] = d[u] + cost[i];
                pq.emplace(d[v], v);
            }
        }
    }
    ll res = d[0];
    if (res >= (1ll<<60)) res = 0;
    cout << res;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}
