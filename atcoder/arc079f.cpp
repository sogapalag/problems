#include <bits/stdc++.h>

using namespace std;


void solve() {
    int n; cin >> n;
    vector<vector<int>> g(n);
    vector<int> p(n);
    for (int i = 0; i < n; i++) {
        int x; cin >> x;
        x--;
        g[x].emplace_back(i);
        p[i] = x;
    }

    // get cycle
    vector<bool> trk(n);
    int x = 0;
    while (!trk[x]) {
        trk[x] = true;
        x = p[x];
    }
    vector<bool> cyc(n);
    while (!cyc[x]) {
        cyc[x] = true;
        x = p[x];
    }

    vector<set<int>> sub(n);
    vector<int> a(n);
    auto mex = [&](int u){
        int i = 0;
        while (sub[u].find(i) != sub[u].end()) {
            i++;
        }
        return i;
    };
    // calc out of cycle
    function<void(int)> dfs = [&](int u){
        for (int v: g[u])if(!cyc[v]){
            dfs(v);
            sub[u].insert(a[v]);
        }
        if (!cyc[u]) {
            a[u] = mex(u);
        }
    };
    for (int i = 0; i < n; i++) {
        if(cyc[i]) dfs(i);
    }

    // two candidate
    auto snd_sub = sub;
    {
        a[x] = mex(x);
        sub[p[x]].insert(a[x]);
        int y = p[x];
        while (y != x) {
            a[y] = mex(y);
            sub[p[y]].insert(a[y]);
            y = p[y];
        }
        if (a[x] == mex(x)) {
            cout << "POSSIBLE"; return;
        }
    }
    swap(snd_sub, sub);
    {
        int pre = mex(x);
        sub[x].insert(pre);
        a[x] = mex(x);
        sub[p[x]].insert(a[x]);
        int y = p[x];
        while (y != x) {
            a[y] = mex(y);
            sub[p[y]].insert(a[y]);
            if (p[y] == x) {
                if (a[y] == pre) {
                    cout << "POSSIBLE"; return;
                }
            }
            y = p[y];
        }
    }
    cout << "IMPOSSIBLE"; return;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
