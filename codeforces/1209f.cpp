#include <bits/stdc++.h>

using namespace std;
const int MOD = 1e9+7; 
const int N = 1e6; 
vector<int> g[N][10];
int vir;
vector<bool> trk(N);
vector<int> res(N);

// i=233, u -2> vir -3> vir' -3> v
void add(int u, int v, int i) {
    auto s = to_string(i);
    int x = u, y = vir;
    for (int i = 0;i < (int)s.size()-1; i++) {
        g[x][s[i]-'0'].emplace_back(y);
        x = y;
        y = ++vir;
    }
    g[x][s.back()-'0'].emplace_back(v);
}

void solve() {
    int n,m;
    cin >> n >> m;
    vir = n;
    for (int i = 1; i <= m; i++) {
        int x,y;
        cin >> x >> y;
        x--;y--;
        add(x,y,i);
        add(y,x,i);
    }

    // bfs
    queue<int> q;
    q.push(0); trk[0] = true;
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        vector<int> sp; // same prefix
        sp.emplace_back(u);
        while (!q.empty() && res[u] == res[q.front()]) {
            sp.emplace_back(q.front()); q.pop();
        }
        // have to process same prefix same time, otherwise u-3>, mey before another node u'-1>
        for (int d = 0; d < 10; d++) {
            for (int c: sp)
            for (int v: g[c][d])if(!trk[v]){
                res[v] = ((long long)10*res[c] + d) % MOD;
                trk[v] = true;
                q.push(v);
            }
        }
    }
    for (int i = 1; i < n; i++) {
        cout << res[i] << "\n";
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
