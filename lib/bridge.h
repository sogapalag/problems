int cnt, tim;
void init(){
    cnt = 0;
    tim = 1;
    memset(low, 0, sizeof low);
    memset(num, 0, sizeof num);
}

// for undirected graph using.
void add_edge(int u, int v, int id){
    edge[cnt] = {v, sson[u], id};
    sson[u] = cnt++;
    edge[cnt] = {u, sson[v], id};
    sson[v] = cnt++;
}

void tarjan(int u, int fa=-1){
    low[u] = num[u] = tim++;
    for (int e=sson[u]; ~e; e=edge[e].bro){
        int v = edge[e].to;
        // here must be this, cannot use v == fa, tarjan(v, u)
        // since there'll be multi-edge, 
        if (e == (fa^1)) continue;
        if (num[v])
            low[u] = min(low[u], num[v]);
        else{
            tarjan(v, e);
            low[u] = min(low[u], low[v]);
            if (low[v] > num[u])//bridge
                // pass
        }
    }
}
