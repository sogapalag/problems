#include <bits/stdc++.h>

using namespace std;

struct Dsu {
    int n;
    vector<int> p;
    vector<int> r;
    
    Dsu(int _n) { n = _n; p.resize(n); r.resize(n); init(); }
    inline void init() {
        for (int i = 0; i < n; i++) {
            p[i] = i;
            r[i] = 1;
        }
    }
    inline int find(int x) {
        return p[x] == x ? x: p[x] = find(p[x]);
    }
    inline bool join(int x, int y) {
        x = find(x); y = find(y);
        if (x == y) return false;
        if (r[x] < r[y]) swap(x, y);
        p[y] = x; r[x] += r[y];
        return true;
    }
    inline bool check(int x, int y) {
        return find(x) == find(y);
    }
    int size(int x) {
        return r[find(x)];
    }
};

int dp[70][1<<17];
bool trk[70][1<<17];

// note the moment we processed all a-edges in kruskal, it would be a forest.
// so if we continue process b-edges, it would be tree of those components
// this imply path of original graph is valid iff it won't re-enter a visited compo. (since it violate above form)
// so make *MSK states, indicate which compo visited.
// then the key speed-up, is we can only track compo-size > 3. since <=3, 2a<2b, i.e. it won't even sats min-dist requirement.
void solve() {
    int n,m,a,b;
    cin >> n >> m >> a >> b;
    vector<vector<pair<int,int>>> g(n);
    Dsu dsu(n);
    for (int _ = 0; _ < m; _++) {
        int x,y,z;
        cin >> x >> y >> z;
        x--;y--;
        if (z == a) dsu.join(x,y);
        g[x].emplace_back(y,z);
        g[y].emplace_back(x,z);
    }
    vector<int> pos(n, -1); int cnt = 0;
    vector<int> belong(n), bit(n);
    for (int i = 0; i < n; i++) {
        if (dsu.find(i) == i && dsu.size(i) > 3) pos[i] = cnt++;
    }
    for (int i = 0; i < n; i++) {
        int x = dsu.find(i);
        belong[i] = x;
        x = pos[x];
        bit[i] = x==-1 ? 0 : (1<<x);
    }
    auto node = [&](int i, int msk){
        return i<<cnt | msk;
    };
    memset(dp, 0x3f, sizeof dp);
    const int MSK = 1<<cnt; 
    using pi = pair<int,int>;
    priority_queue<pi,vector<pi>,greater<pi>> pq;
    dp[0][bit[0]] = 0; pq.emplace(0, node(0,bit[0]));
    while (!pq.empty()) {
        int dis, nd;
        tie(dis, nd) = pq.top(); pq.pop();
        int i = nd>>cnt, msk = nd%MSK;
        if (trk[i][msk]) continue;
        trk[i][msk] = true;
        for (auto& _: g[i]) {
            int j,w;
            tie(j,w) = _;
            // belong check needed, since might use 1 edge re-enter
            if (w == b && (belong[i]==belong[j] || (msk&bit[j]))) continue;
            int nxt = msk | bit[j];
            if (dp[j][nxt] > dp[i][msk] + w) {
                dp[j][nxt] = dp[i][msk] + w;
                pq.emplace(dp[j][nxt], node(j,nxt));
            }
        }
    }
    for (int i = 0; i < n; i++) {
        cout << *min_element(dp[i], dp[i]+MSK) << ' ';
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}
