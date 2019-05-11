#include <bits/stdc++.h>

using namespace std;

typedef vector<int> vi;

#define sz(x) (int)(x).size()
#define mp make_pair
#define pb push_back
#define f first
#define s second

const int N = 1e5 + 5;
int n;
vi res;

map<int, multiset<int>> graph;

void gg(){
    cout << -1 << '\n';
    exit(0);
}

int entry(){
    int cnt = 0; // count #odd degree
    int res = 1; // if all even-degree, any entry.
    for (auto &v: graph){
        if (sz(v.s) & 1){
            cnt += 1;
            res = v.f;
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
    res.pb(vtx); //a reverse chain. however valid
}

void print(){
    if (sz(res) != n)
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
