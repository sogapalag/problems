#include <bits/stdc++.h>

using namespace std;

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
int g[20][20];
// once you feel prob is high, random.
void solve() {
    int n,m;
    cin >> n >> m;
    const int TRY = 100*(n+m); 
    const int JUMP = 25; 
    for (int _ = 0; _ < TRY; _++) {
        vector<int> a(n*m);
        iota(a.begin(), a.end(), 0);
        vector<pair<int, int>> res;
        auto take = [&](int step, int i){
            int x = a[i];
            g[x/m][x%m] = step;
            res.emplace_back(x/m, x%m);
            swap(a[i], a[a.size()-1]); a.pop_back();
            return x;
        };
        int k = rng() % a.size();
        int now = take(0, k);
        for (int s = 1; s < n*m; s++) {
            for (int _ = 0; _ < JUMP; _++) {
                int k = rng() % a.size();
                int nxt = a[k];
                if (now%m == nxt%m) continue;
                if (now/m == nxt/m) continue;
                if (now%m + now/m == nxt%m + nxt/m) continue;
                if (now%m - now/m == nxt%m - nxt/m) continue;
                now = take(s, k);
                goto next_step;
            }
            goto one_fail;
next_step:;
        }
        // success
        cout << "POSSIBLE\n";
        for (auto& _: res) {
            cout << _.first+1 << ' ' << _.second+1 << '\n';
        }
        //for (int i = 0; i < n; i++) {
        //    for (int j = 0; j < m; j++) {
        //        cout << g[i][j]+1 << ' ';
        //    }cout << '\n';
        //}
        return;
one_fail:;     
    }
    cout << "IMPOSSIBLE\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int T; cin >> T;
    for (int t = 1; t <= T; t++) {
        cout << "Case #" << t << ": ";
        solve();
        //cout << "\n";
    }
    fflush(stdout);
}
