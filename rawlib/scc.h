#include <bits/stdc++.h>

using namespace std;

const int MX = 100003;


/////////////////////////////////////////////////////
//     Kosaraju's algorithm
//  first dfs forest, get finish time order of nodes
//  second _dfs on rev-graph, with ft decrasing order
//    every loop call _dfs means enter a new scc.
/////////////////////////////////////////////////////


int n; // #nodes [1..n]
char color[MX];
vector<int> ft; // node in finish time order
map<int, multiset<int>> graph;
map<int, multiset<int>> revph;


void dfs(int v){
    color[v] = 's';
    for (auto u: graph[v]){
        if (color[u] == '0')
            dfs(u);
    }
    color[v] = 'e';
    ft.push_back(v);
}
void full_dfs(){
    memset(color, '0', sizeof color);
    for (int v = 1, v <= n; v++){
        if (color[v] == '0')
            dfs(v);
    }
}
void rev_graph(){
    for (auto &p: graph){
        int v = p.first;
        for (auto u: p.second){
            revph[u].insert(v);
        }
    }
}

void _dfs(int v){
    color[v] = 's';
    // do something here in some node of scc.
    for (auto u: revph[v]){
        if (color[u] == '0')
            _dfs(u);
    }
    color[v] = 'e';
}
void scc_dfs(){
    memset(color, '0', sizeof color);
    for (int i = n; i >= 1; i--) {
        int v = ft[i];
        // scc entry
        if (color[v] == '0'){
            // in scc
            _dfs(v);
            // out scc
        }
    }
}

void solve() {
    ft.reserve(n+1); ft.push_back(-1);
    full_dfs();
    rev_graph();
    scc_dfs();
}

