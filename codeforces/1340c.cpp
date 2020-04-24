#include <bits/stdc++.h>

using namespace std;

const int N = 1e4+10; 
const int K = 1024; 
int d[N][K];

// a naive thought, i->j form : d(simple path) + (mid*)x2 + (left*,right*)x2 = G
//  note left differ mid, some alternating.
//  but this seem unsolvable.
// correct way, node (i,t), t indicate time
// each (i,t) -> (i+-1, tt=t+w{<=G}) by cost 0.
// (i,G)->(i,0) by cost G+R. i.e. we've move G cost to this part, without affecting correctness.
// thus 01bfs
void solve() {
    int D, n;
    cin >> D >> n;
    vector<int> a(n);
    for (auto& x: a) cin >> x;
    sort(a.begin(), a.end());
    int G, R;
    cin >> G >> R;
    
    memset(d, 0x3f, sizeof d);
    deque<pair<int, int>> q;
    d[0][0] = 0;
    q.emplace_back(0, 0);
    while (!q.empty()) {
        int i,t;
        tie(i,t) = q.front(); q.pop_front();
        for (int ii:{i-1,i+1})if(0<=ii&&ii<n){
            int tt = t + abs(a[ii]-a[i]);
            if (tt <= G && d[ii][tt] > d[i][t]) {
                d[ii][tt] = d[i][t];
                q.emplace_front(ii,tt);
            }
        }
        if (t == G && d[i][0] > d[i][t] + G+R) {
            d[i][0] = d[i][t] + G+R;
            q.emplace_back(i,0);
        }
    }
    int res = 0x3f3f3f3f;
    for (int i = 0; i < n; i++) {
        int x = a[i];
        if (D-x <= G) {
            res = min(res, d[i][0] + D-x);
        }
    }
    if (res == 0x3f3f3f3f) res = -1;
    cout << res;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}
