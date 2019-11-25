#include <bits/stdc++.h>

using namespace std;

const int N = 2e5+10; 
int c[N], sta[N], fin[N], tim, mx[N][2];
vector<int> g[N], tour[N][2];

// mx[u][i] : [1..u]'s i-th mx
// tour[x][i] : x as i-th mx in the tour
void prep_tour(int u, int p) {
    sta[u] = tim++;
    for (int i = 0; i < 2; i++) {
        tour[mx[u][i]][i].emplace_back(sta[u]);
    }
    for (int v: g[u])if(v!=p){
        mx[v][0] = max(v, mx[u][0]);
        mx[v][1] = max(min(v,mx[u][0]), mx[u][1]);
        prep_tour(v, u);
    }
    fin[u] = tim;
}

int down(int u, const vector<int>& t) {
    return lower_bound(t.begin(), t.end(), fin[u]) - lower_bound(t.begin(), t.end(), sta[u]);
}

void dfs(int u, int p, int mp, int mg) {
    c[u] = c[p];
    if (u > mg) {
        c[u] += down(u, tour[mp][u>mp]);
    } else if (mp > mg) {
        c[u] += down(u, tour[mp][0]) - down(u, tour[mg][1]);
    }
    for (int v: g[u])if(v!=p){
        dfs(v, u, max(mp, u), max(mg, p));
    }
}

void solve() {
    int n; cin >> n;
    for (int _ = 1; _ < n; _++) {
        int x,y;
        cin >> x >> y;
        g[x].push_back(y);
        g[y].push_back(x);
    }
    mx[1][0] = 1; prep_tour(1, 0);
    dfs(1, 0, 1, 1);
    for (int i = 2; i <= n; i++) {
        cout << c[i] << ' ';
    }
}


int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
