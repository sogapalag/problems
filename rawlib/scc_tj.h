#include <bits/stdc++.h>

using namespace std;
 
const int MX = 100003;

///////////////////////////////////////////////
//    tarjan
//    since sccs DAG, imagine last scc' root, 
//    would be iff low==num, and nodes in this scc, same low.
//
//    NOTE: nodes not [1..n] index, need some fix.


int n; // nodes [1..n]

int tim; 
int low[MX];
int num[MX];
bool trk[MX];
vector<int> stk;
map<int, multiset<int>> graph;


//ll gloc, gcnt;

void tarjan(int v){
    low[v] = num[v] = tim++;
    stk.push_back(v);
    trk[v] = true;
    for (auto u: graph[v]){
        if (!num[u])
            tarjan(u);
        if (trk[u])
            low[v] = min(low[v], low[u]);
    }
    // into scc
    if (low[v] == num[v]){
        // init scc sub_glob here
        while(1){
            int k = stk.back();
            stk.pop_back(); trk[k] = false;
            // calc this scc's nodes here
            if (k == v)
                break;
        }
        // calc scc sub_glob here
    }
}

void run(){
    // set global val here
    stk.reserve(n);
    tim = 1;
    memset(low, 0, sizeof low);
    memset(num, 0, sizeof num);
    memset(trk, 0, sizeof trk);
    for (int v = 1; v <= n; v++) {
        if (!num[v])
            tarjan(v);
}

void solve() {
    run();
}
