
#include <bits/stdc++.h>

using namespace std;

// SNIPPETS_START graph_sim_scc_tarjan
struct Graph {
    int n, m;
    vector<vector<int>> g;
/////////////////////////////////////
// algo work for multi-edge, change vector<multiset<int>> g;
// remove above, attach snip, or overrite
/////////////////////////////////////
    int tim;
    vector<int> low;
    vector<int> num;
    vector<bool> trk;
    vector<int> stk;
    void scc_dfs(int u);
    void scc_run();
};

//int gloc, glocnt;

void Graph::scc_dfs(int u) {
    low[u] = num[u] = tim++;
    stk.emplace_back(u);
    trk[u] = true;
    for (int v: g[u]){
        if (!num[v])
            scc_dfs(v);
        if (trk[v])
            low[u] = min(low[u], low[v]);
    }
    // into scc
    if (low[u] == num[u]){
        // init scc sub_glob here
        while(true){
            int k = stk.back();
            stk.pop_back(); trk[k] = false;
            // calc this scc's nodes here
            if (k == u)
                break;
        }
        // calc scc sub_glob here
    }
}

void Graph::scc_run(){
    // set global val here
    stk.reserve(n);
    tim = 1;
    low = vector<int>(n+1, 0);
    num = vector<int>(n+1, 0);
    trk = vector<bool>(n+1, false);
    for (int u = 1; u <= n; u++) {
        if (!num[u])
            scc_dfs(u);
    }
}
// SNIPPETS_END
