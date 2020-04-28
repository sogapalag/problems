#include <bits/stdc++.h>

using namespace std;
using ll=long long;

const int N = 52; 
const int C = 2555; 
ll d[N][C+1];

struct State {
    ll dis;
    int i, t;
    State() {}
    State(ll _dis, int _i, int _t) : dis(_dis), i(_i), t(_t) {}
    bool operator<(const State& _oth) const {
        return dis > _oth.dis;
    }
};
void solve() {
    int n,m,S;
    cin >> n >> m >> S;
    vector<vector<tuple<int,int,int>>> g(n);
    for (int _ = 0; _ < m; _++) {
        int x,y,a,b;
        cin >> x >> y >> a >> b;
        --x,--y;
        g[x].emplace_back(y, a, b);
        g[y].emplace_back(x, a, b);
    }
    vector<pair<int,int>> charge(n);
    for (auto& x: charge) {
        cin >> x.first >> x.second;
    }

    memset(d, 0x3f, sizeof d);
    S = min(S, C);
    d[0][S] = 0;
    priority_queue<State> pq;
    pq.emplace(0,0,S);
    while (!pq.empty()) {
        auto _ = pq.top(); pq.pop();
        ll dis = _.dis;int i = _.i, t = _.t;
        if (dis > d[i][t]) continue;
        for (auto [j,a,b]: g[i]) if (a<=t){
            if (d[j][t-a] > dis + b) {
                d[j][t-a] = dis + b;
                pq.emplace(d[j][t-a], j, t-a);
            }
        }
        if (t < C) {
            int tt = min(C, t+charge[i].first);
            if (d[i][tt] > dis + charge[i].second) {
                d[i][tt] = dis + charge[i].second;
                pq.emplace(d[i][tt], i, tt);
            }
        }
    }
    for (int i = 1; i < n; i++) {
        ll res = *min_element(d[i], d[i]+C+1);
        cout << res << "\n";
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}
