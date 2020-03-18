#include <bits/stdc++.h>

using namespace std;

const int N = 5012; 
int g[N*N], pos[N*N]; // 5s->2.5s
void solve() {
    int x, a, b, c, d;
    //cin >> x >> a >> b >> c >> d;
    scanf("%d %d %d %d %d", &x,&a,&b,&c,&d);
    auto rng = [&](){
        return x = (1ll*a*x*x + 1ll*b*x + c) % d;
    };
    int n,m,q;
    //cin >> n >> m >> q;
    scanf("%d %d %d", &n,&m,&q);
    //vector<int> g(n * m);
    //iota(g.begin(), g.end(), 0);
    for (int i = 0; i < n*m; i++) {
        g[i] = i;
        swap(g[i], g[rng()%(i+1)]);
    }
    for (int _ = 0; _ < q; _++) {
        int u,v;
        //cin >> u >> v;
        scanf("%d %d", &u,&v);
        u--;v--;
        swap(g[u], g[v]);
    }

    //vector<int> pi(n*m), pj(n*m);
    //for (int k = 0; k < n*m; k++) {
    //    pi[g[k]] = k/m;
    //    pj[g[k]] = k%m;
    //}
    //vector<int> pos(n*m);
    for (int k = 0; k < n*m; k++) {
        pos[g[k]] = k;
    }
    vector<int> l(n, 0), r(n, m);
    for (int x = 0; x < n*m; x++) {
        //int i = pi[x];
        //int j = pj[x];
        int i = pos[x]/m;
        int j = pos[x]%m;
        if (l[i] <= j && j < r[i]) {
            //cout << x+1 << ' ';
            printf("%d ", x+1);
            for (int ii = 0; ii < i; ii++) {
                r[ii] = min(r[ii], j+1);
            }
            for (int ii = i+1; ii < n; ii++) {
                l[ii] = max(l[ii], j);
            }
        }
    }
}

int main() {
    //ios_base::sync_with_stdio(false);
    //cin.tie(NULL);
    solve();
    return 0;
}
