#include <bits/stdc++.h>

using namespace std;

#define to first
#define id second

void solve() {
    int n,m,k;
    cin >> n >> m >> k;
    for (int _ = 0; _ < n; _++) {
        int _w; cin >> _w; // irrelevant, since we can always color all edge
    }
    vector<vector<pair<int,int>>> g(n);
    vector<int> co(m, -1);
    auto freq = [&](int u){
        vector<int> cnt(k);
        for (auto& e: g[u]) {
            cnt[co[e.id]]++;
        }
        int mi = *min_element(cnt.begin(), cnt.end());
        for (auto& x: cnt) {
            x -= mi;
            assert(x <= 2);
        }
        return cnt;
    };
    vector<int> path;
    vector<bool> trk(m);
    function<void(int,int,int)> dfs = [&](int u, int a, int b) {
        for (auto& e: g[u]) {
            if (!trk[e.id] && co[e.id] == a) {
                path.push_back(e.id); trk[e.id] = true;
                dfs(e.to, b, a); break;
            }
        }
    };
    vector<int> colors(k);
    iota(colors.begin(), colors.end(), 0);
    for (int i = 0; i < m; i++) {
        int x,y;
        cin >> x >> y;
        x--;y--;
        auto fx = freq(x), fy = freq(y);
        int a = -1, b = -1, c = -1;
        for (int j: colors) {
            if (fx[j] < 2 && fy[j] < 2) {
                c = j; break;
            }
            if (fx[j] == 0) b = j;
            if (fy[j] == 0) a = j;
        }
        // flip a abababa.. edge_tour-chain, vertex could repeat
        // thus still valid, and we can co[i]=a
        if (c == -1) {
            assert(a != -1 && b != -1);
            path.clear();
            fill(trk.begin(), trk.end(), 0);
            dfs(x, a, b);
            for (int eid: path) {
                co[eid] = co[eid]==a? b : a;
            }
            c = a;
        }
        co[i] = c;
        g[x].emplace_back(y, i);
        g[y].emplace_back(x, i);
    }
    for (auto& x: co) {
        cout << x+1 << "\n";
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
