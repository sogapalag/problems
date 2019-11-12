#include <bits/stdc++.h>

using namespace std;
using ll=long long;
using pi=pair<int, ll>;
const int inf = 0x3f3f3f3f;

const int V = 2048;
const int E = (V*5)<<2;
int sson[V], pre[V], trk[V]; ll dis[V];
int cnt;

struct node{
    int to, bro, cap, flow; ll cost;
} edge[E];

void init(){
    cnt = 0;
    memset(sson, -1, sizeof sson);
}

void add_edge(int u, int v, int cap, ll cost){
    edge[cnt] = {v, sson[u], cap, 0, cost};
    sson[u] = cnt++;
    edge[cnt] = {u, sson[v], 0, 0, -cost};
    sson[v] = cnt++;
}

bool spfa(int s, int t){
    queue<int> q;
    memset(pre, -1, sizeof pre);
    memset(dis, inf, sizeof dis);
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

pi mcmf(int s, int t){
    int flow = 0; ll cost = 0;
    while (spfa(s, t)){
        int f = inf;
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
int dx[4] = {1, -1, 1, -1};
int dy[4] = {1, -1, -1, 1};
// trick, split manhaten to 4 type coeff
// a flow ensure red type i = blue type i, careful contribution is dual
void solve() {
    int n; cin >> n;
    init();
    int S = 4, T = 5;
    int v = 6;
    for (int _ = 0; _ < n; _++) {
        int x,y,z;
        cin >> x >> y >> z;
        add_edge(S, v, z, 0);
        for (int i = 0; i < 4; i++) {
            ll cost = x*dx[i] + y*dy[i];
            add_edge(v, i, z, cost);
        }
        v++;
    }
    for (int _ = 0; _ < n; _++) {
        int x,y,z;
        cin >> x >> y >> z;
        add_edge(v, T, z, 0);
        for (int i = 0; i < 4; i++) {
            ll cost = x*dx[i^1] + y*dy[i^1];
            add_edge(i, v, z, cost);
        }
        v++;
    }

    ll res = -mcmf(S,T).second;
    cout << res;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
