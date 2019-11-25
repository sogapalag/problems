#include <bits/stdc++.h>

using namespace std;

const int N = 2e5+10; 
int c[N];
vector<int> g[N];

int down(int u, int p, int lim) {
    int sum = 0;
    for (int v: g[u])if(v!=p){
        if (v < lim) sum += 1 + down(v, u, lim);
    }
    return sum;
}

// mp max[1..p] p = pa(u)
// mg max[1..g] g = pa(p)
void dfs(int u, int p, int mp, int mg) {
    c[u] = c[p];
    if (u > mg) {
        c[u] += 1 + down(u, p, mp);
    } else if (mp > mg) {
        c[u] += down(u, p, mp) - down(u, p, mg);
    }
    for (int v: g[u])if(v!=p){
        dfs(v, u, max(mp, u), max(mg, p));
    }
}

// looks like O(n^2), but note 
//   u>mg, mp>mg require mono-inc
//   down implies mono-inc pause. this ensure total explore O(n)
void solve() {
    int n; cin >> n;
    for (int _ = 1; _ < n; _++) {
        int x,y;
        cin >> x >> y;
        g[x].push_back(y);
        g[y].push_back(x);
    }
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
