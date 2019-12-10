#include <bits/stdc++.h>

using namespace std;
using ll=long long;

void solve() {
    int n,m,CAP,c0;
    cin >> n >> m >> CAP >> c0;
    vector<tuple<int,int,int>> evs(n);
    for (int i = 0; i < n; i++) {
        int x,y,z;
        cin >> x >> y >> z;
        evs[i] = {x,y,z};
    }
    evs.emplace_back(m, 0, 0);
    sort(evs.begin(), evs.end());

    map<int,int> resources; // till now, could use
    resources[0] = c0;
    int vol = c0, x = 0;

    ll res = 0;
    for (auto& _: evs) {
        int t,cap,cost;
        tie(t,cap,cost) = _;
        int dist = t-x; x = t;
        // use best to finish required dist
        while (!resources.empty() && dist > 0) {
            auto best = resources.begin();
            int use = min(best->second, dist);
            res += (ll)use * best->first;
            dist -= use;
            vol -= use;
            best->second -= use;
            if (best->second == 0) resources.erase(best);
        }
        if (dist > 0) {
            cout << "-1\n"; return;
        }
        int can_join = min(CAP - vol, cap);
        vol += can_join;
        int may_better = cap - can_join;
        // for >CAP, find better replacement, since future could use
        while (may_better > 0 && !resources.empty()) {
            auto worst = --resources.end();
            if (worst->first <= cost) break;
            int repla = min(may_better, worst->second);
            can_join += repla;
            may_better -= repla;
            worst->second -= repla;
            if (worst->second == 0) resources.erase(worst);
        }
        resources[cost] += can_join;
    }
    cout << res << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int t; cin >> t;
    while(t--)solve();
    cout << endl;
}
