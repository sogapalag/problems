#include <bits/stdc++.h>

using namespace std;
using pi=pair<int, int>;
const int inf = 0x3f3f3f3f;

const int V = 512;
const int E = 10010<<2;
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


void solve() {
    int n,m;
    cin >> n >> m;
    vector<string> s(n);    
    for (int i = 0; i < n; i++) {
        cin >> s[i];
    }
    pair<int, int> Sp, Tp;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (s[i][j] == 'S') Sp ={i,j};
            if (s[i][j] == 'T') Tp ={i,j};
        }
    }
    if (Sp.first == Tp.first || Sp.second == Tp.second) {
        cout << -1; return;
    }

    init();
    int S = 0, T = n+m+1;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (s[i][j]=='o') {
                add_edge(i+1, n+j+1, 1, 0);
                add_edge(n+j+1, i+1, 1, 0);
            }
            if (s[i][j]=='S') {
                add_edge(S, i+1, inf, 0);
                add_edge(i+1, S, inf, 0);
                add_edge(S, n+j+1, inf, 0);
                add_edge(n+j+1, S, inf, 0);
            }
            if (s[i][j]=='T') {
                add_edge(T, i+1, inf, 0);
                add_edge(i+1, T, inf, 0);
                add_edge(T, n+j+1, inf, 0);
                add_edge(n+j+1, T, inf, 0);
            }
        }
    }

    int res = mcmf(S,T).first;
    cout << res;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
