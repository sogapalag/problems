#include <bits/stdc++.h>

using namespace std;
using pi=pair<int, int>;
const int V = 1500;
const int E = 7600<<2;
const int inf = 0x3f3f3f3f;
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

const int N = 55; 
int g[N][N];
int eid[N][N];
int deg[N], rem[N];

// let (indeg, outdeg)
// cycle =  { (1,1) (1,1) (1,1) }
// non-cycle = { (1,1), (2,0), (0,2) }
// now focus on (out)deg. if u has deg=k, then there exist C(k,2) non-cycle.
// so #cycle = C(n,3) - sum_u C(deg_u, 2) = const - sum deg_u^2
// so min sum deg^2. for each undecided, create Y-shape edges, then for each u create cost = d(deg^2) = 2*d+1, edges to T.
void solve() {
    int n,m;
    cin >> n >> m;
    memset(g, -1, sizeof g);
    for (int _ = 0; _ < m; _++) {
        int x,y;
        cin >> x >> y;
        x--;y--;
        g[x][y] = 1; deg[x]++;
        g[y][x] = 0;
    }
    init();
    int S = n, T = n+1;
    int v = T+1;
    for (int i = 0; i < n; i++) {
        for (int j = i+1; j < n; j++) {
            if (g[i][j] == -1) {
                rem[i]++; rem[j]++;
                add_edge(S, v, 1, 0);
                eid[i][j] = cnt; add_edge(v, i, 1, 0);
                add_edge(v, j, 1, 0);
                v++;
            }
        }
    }
    for (int i = 0; i < n; i++) {
        int d = deg[i], r = rem[i];
        for (int k = 1; k <= r; k++) {
            add_edge(i, T, 1, 2*d+1); d++;
        }
    }
    mcmf(S, T);

    for (int i = 0; i < n; i++) {
        g[i][i] = 0;
        for (int j = i+1; j < n; j++) {
            if (g[i][j] == -1) {
                int k = eid[i][j];
                k = edge[k].flow;
                g[i][j] = k;
                g[j][i] = k^1;
            }
        }
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cout << g[i][j];
        }cout << "\n";
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
