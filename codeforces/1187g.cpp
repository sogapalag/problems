#include <bits/stdc++.h>

using namespace std;

using pi=pair<int, int>;
const int inf = 0x3f3f3f3f;
const int V = 10005;
const int E = (1000'000)<<1;
int sson[V], pre[V], dis[V], trk[V];
int cnt;

struct node{
    int to, bro, cap, flow, cost;
} edge[E];

void init(){
    cnt = 0;
    memset(sson, -1, sizeof sson);
}

void add_edge(int u, int v, int cap, int cost){
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
    int flow = 0, cost = 0;
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

// each node, span more nodes t=1.. time 
// u->v span on time-dim also on k-dim
void solve() {
    init();
    int n, m, k, c, d;
    cin >> n >> m >> k >> c >> d;
    const int TIM = 100; 
    int S = 0, T = n*TIM + 1;
    for (int i = 1; i <= TIM; i++) {
        add_edge(i, T, 100, 0);
    }
    auto f = [&](int u, int tim){
        assert(tim <= TIM);
        return u*TIM+tim;
    };
    for (int _ = 0; _ < k; _++) {
        int x; cin >> x;
        x--;
        add_edge(S, f(x,1), 1, 0);
    }
    for (int x = 0; x < n; x++) {
        for (int t = 1; t < TIM; t++) {
            // wait
            add_edge(f(x,t), f(x,t+1), 100, c);
        }
    }
    for (int _ = 0; _ < m; _++) {
        int u, v; cin >> u >> v;
        u--; v--;
        for (int t = 1; t < TIM; t++) {
            for (int j = 1; j <= k; j++) {
                add_edge(f(u, t), f(v, t+1), 1, c + d * (2*j-1));
                add_edge(f(v, t), f(u, t+1), 1, c + d * (2*j-1));
            }
        }
    }
    int res = mcmf(S, T).second;
    cout << res;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
