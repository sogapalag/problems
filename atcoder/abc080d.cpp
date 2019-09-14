#include <bits/stdc++.h>

using namespace std;


void solve() {
    int n, C;
    cin >> n >> C;
    vector<vector<pair<int,int>>> t(100005);
    for (int _ = 0; _ < n; _++) {
        int x,y,z;
        cin >> x >> y >> z; z--;
        t[x].emplace_back(1, z);
        t[y].emplace_back(0, z);
    }
    vector<int> status(C);
    int free = 0, soft = 1, use = 2;
    int cnt = 0, res = 0;
    for (int i = 1; i < 100005; i++) {
        sort(t[i].begin(), t[i].end());
        // free previous soft
        for (int j = 0; j < C; j++) {
            if (status[j] == soft) {
                status[j] = 0;
                cnt--;
            }
        }
        for (auto& p: t[i]) {
            int k,z;
            tie(k,z) = p;
            // ')'
            if (!k) {
                status[z] = soft;
            } else {// '['
                assert(status[z] < use);
                if (status[z] == free) cnt++;
                status[z] = use;
                res = max(res, cnt);
            }
        }
    }
    cout << res;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
