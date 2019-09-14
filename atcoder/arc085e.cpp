#include <bits/stdc++.h>

using namespace std;

using ll=long long ;
using pl=pair<ll, ll> ;

const int V = 150;
const int E = 500<<2;
int sson[V], pre[V]; ll dis[V]; int trk[V];
int cnt;

struct node{
    int to, bro; ll cap, flow; int cost;
} edge[E];

void init(){
    cnt = 0;
    memset(sson, -1, sizeof sson);
}

void add_edge(int u, int v, ll cap, int cost){
    edge[cnt] = {v, sson[u], cap, 0, cost};
    sson[u] = cnt++;
    edge[cnt] = {u, sson[v], 0, 0, -cost};
    sson[v] = cnt++;
}

const long long inf = 0x3f3f3f3f3f3f3f3f;
bool spfa(int s, int t){
    queue<int> q;
    memset(pre, -1, sizeof pre);
    //memset(dis, inf, sizeof dis);
    for (int i = 0; i < V; i++) {
        dis[i] = inf;
    }
    memset(trk, 0, sizeof trk);
    dis[s] = 0; trk[s] = 1; q.push(s);
    while(!q.empty()){
        int u = q.front(); q.pop(); trk[u] = 0;
        for (int e=sson[u]; ~e; e=edge[e].bro){
            int v = edge[e].to;
            if (edge[e].cap > edge[e].flow && dis[v] > dis[u] + edge[e].cost){
                dis[v] = dis[u] + edge[e].cost;
                pre[v] = e;
                if (!trk[v]){
                    trk[v] = 1;
                    q.push(v);
                }
            }
        }
    }
    return pre[t] != -1;
}

pl mcmf(int s, int t){
    ll flow = 0, cost = 0;
    while (spfa(s, t)){
        ll f = inf;
        for (int e=pre[t]; ~e; e=pre[edge[e^1].to])
            f = min(f, edge[e].cap - edge[e].flow);
        for (int e=pre[t]; ~e; e=pre[edge[e^1].to]){
            edge[e].flow += f;
            edge[e^1].flow -= f;
            cost += edge[e].cost * f;
        }
        flow += f;
    }
    return {flow, cost};
}

void solve() {
    int n; cin >> n;
    vector<int> a(n);
    long long TOT = 0;
    for (auto& x: a) {
        cin >> x;
        if (x > 0) TOT += x;
    }
    int S = 0, T = n+1;
    init();
    for (int i = 0; i < n; i++) {
        if (a[i] > 0) {
            add_edge(i+1, T, a[i], 0);
        }else {
            add_edge(S, i+1, -a[i], 0);
        }
    }
    for (int i = 1; i <= n; i++) {
        for (int j = i*2; j <= n; j+=i) {
            add_edge(i, j, inf, 0);
        }
    }
    auto res = mcmf(S, T);
    ll ans = TOT - res.first;
    cout << ans;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
