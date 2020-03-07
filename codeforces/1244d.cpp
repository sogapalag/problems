#include <bits/stdc++.h>

using namespace std;
#define rep(i) for(int i:{0,1,2})
using ll=long long;
const int N = 100005; 
int cost[3][N];

void solve() {
    int n; cin >> n;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < n; j++) {
            cin >> cost[i][j];
        }
    }
    vector<vector<int>> g(n);
    vector<int> deg(n);
    for (int _ = 1; _ < n; _++) {
        int x,y;
        cin >> x >> y;
        x--;y--;
        deg[x]++;deg[y]++;
        g[x].push_back(y);
        g[y].push_back(x);
    }
    if (*max_element(deg.begin(), deg.end()) > 2) {
        cout << -1; return;
    }
    int r = find(deg.begin(), deg.end(), 1) - deg.begin();
    vector<int> line;
    vector<bool> trk(n);
    {
        while ((int)line.size() < n) {
            line.push_back(r);
            trk[r] = true;
            int x;
            for (int y:g[r])if(!trk[y])x=y;
            r=x;
        }
    }
    
    ll res = 1e18;
    vector<int> certi(n);
    int seg[3];
    rep(fi)rep(se)if(fi!=se){
        seg[0]=fi;
        seg[1]=se;
        seg[2]=3-fi-se;
        ll tmp = 0;
        vector<int> co(n);
        for (int _ = 0; _ < n; _++) {
            int u = line[_];
            co[u] = seg[_%3];
            tmp += cost[co[u]][u];
        }
        if (tmp < res) {
            res = tmp;
            certi = co;
        }
    }
    cout << res << '\n';
    for (auto& x: certi) {
        cout << x+1 << ' ';
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}
