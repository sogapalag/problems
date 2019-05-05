// https://www.topcoder.com/community/competitive-programming/tutorials/maximum-flow-section-1/
// https://www.cs.princeton.edu/~wayne/cs423/lectures/max-flow-applications-4up.pdf
// https://www.topcoder.com/community/competitive-programming/tutorials/minimum-cost-flow-part-two-algorithms/
// https://cp-algorithms.com/graph/edmonds_karp.html
// https://cp-algorithms.com/graph/min_cost_flow.html

const int V = 512;
const int E = 512<<2;
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
