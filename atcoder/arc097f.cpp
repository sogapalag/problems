#include <bits/stdc++.h>

using namespace std;


void solve() {
    int n; cin >> n;
    vector<vector<int>> g(n);
    vector<int> deg(n, 0);
    for (int i = 1; i < n; i++) {
        int x,y;
        cin >> x >> y;
        x--; y--;
        deg[x]++; deg[y]++;
        g[x].emplace_back(y);
        g[y].emplace_back(x);
    }
    string s; cin >> s;
    vector<bool> blk(n, false);
    queue<int> q;
    for (int i = 0; i < n; i++) {
        if (deg[i]==1 && s[i]=='B') {
            blk[i] = true;
            q.push(i);
        }
    }
    // remove black leaves
    while (!q.empty()) {
        int v = q.front(); q.pop();
        for (int u: g[v]) {
            if (blk[u]) continue;
            deg[u]--;
            if (deg[u]==1 && s[u]=='B') {
                blk[u] = true;
                q.push(u);
            }
        }
    }
    // since each edge pass twice, dust means might extra filp
    vector<bool> dust(n);
    int sum = 0, root = -1;
    for (int i = 0; i < n; i++) {
        if (blk[i]) continue;
        sum += 2;
        dust[i] = (s[i]=='W') ^ (deg[i]&1);
        sum += dust[i];
        root = i;
    }
    sum -= 2;
    // all black
    if (root == -1) {
        cout << 0; return;
    }
    // one white
    if (sum == 1) {
        cout << 1; return;
    }
    vector<int> arm(n); // longest path (sub u) to u
    int mx = 0;
    // for each, find two largest arm, get path trough u
    function<void(int,int)> dfs = [&](int u, int p){
        int a1=0, a2=0;
        for (int v: g[u]) {
            if (v==p || blk[v]) continue;
            dfs(v, u);
            int a = arm[v];
            if (a > a1) swap(a,a1);
            if (a > a2) swap(a,a2);
        }
        mx = max(mx, a1+a2+dust[u]);
        arm[u] = a1 + dust[u];
    };
    dfs(root, -1);
    // note for path s-t, #op = L+N-D = 2L-2D, where N+D=L. aka, select the path decrease 2D ops.
    int res = sum - 2*mx;
    cout << res;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
