#include <bits/stdc++.h>

using namespace std;

const int N = 1e5 + 5;
int n;
vector<int> res;

map<int, multiset<int>> graph;

void gg(){
    cout << -1 << '\n';
    exit(0);
}

int entry(){
    int cnt = 0; // count #odd degree
    int res = 1; // if all even-degree, any entry.
    for (auto &v: graph){
        if (v.second.size() & 1){
            cnt += 1;
            res = v.first;
        }
    }
    if (cnt > 2)
        gg(); // entry candidate. > 2
    return res;
}

// Hierholzer’s
void dfs(int vtx){
    while (!graph[vtx].empty()){
        auto it = graph[vtx].begin();
        int nei = *it;
        graph[vtx].erase(it);            // crash if it = rit
        auto rit = graph[nei].find(vtx); // must below above line
        graph[nei].erase(rit); // if val, will erase all; we only one.
        dfs(nei);
    }
    res.push_back(vtx); //a reverse chain. however valid
}

void print(){
    if (res.size() != n)
        gg(); // not connected
    for (auto k: res)
        cout << k << ' ';
}

// with thm each degree even(aka, in-to-out), except entry(end).
// with verify path length, i.e. connectivity.
void solve() {
    int ent = entry();
    res.reserve(n);
    dfs(ent);
    print();
}
