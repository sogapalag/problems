#include <bits/stdc++.h>

using namespace std;

// first one might thought a form like:
//  /\/\/ .. where / is direct move, \ is tele. then thought a pair-up algo
// but check the sample input, the case
//         ...
//   ...
// .
// ans = 7. the special part is some tele used twice.
// so a guess, all points on the slope can be used.
// luckily it's true. but rigorous might be hard.
// basically draw some, one can notice, a line with even is easy to connect.
// then remain some odds, then we can use the pattern of sample to connect them.
// finally, we can use tele to add 2/1 more, by parity of points we have now.
void solve() {
    int n; cin >> n;
    vector<pair<int, int>> a(n);
    for (auto& x: a) {
        cin >> x.first >> x.second;
    }
    int res = min(2, n);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < i; j++) {
            int dx = a[i].first - a[j].first;
            int dy = a[i].second- a[j].second;
            //vector<bool> trk(n);
            int p = 0;
            for (int u = 0; u < n; u++) {
                for (int v = 0; v < n; v++) if(u!=v){
                    int x = a[u].first - a[v].first;
                    int y = a[u].second- a[v].second;
                    if (x*1ll*dy==y*1ll*dx) {
                        p++; //trk[u]=trk[v]=true;
                        break;
                    }
                }
            }
            if (p&1) {
                res = max(res, p + min(1, n-p));
            } else {
                res = max(res, p + min(2, n-p));
            }
            //res = max(res, p + min(2, n-p));
        }
    }
    cout << res << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int T; cin >> T;
    for (int t = 1; t <= T; t++) {
        cout << "Case #" << t << ": ";
        solve();
    }
    return 0;
}
