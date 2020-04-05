#include <bits/stdc++.h>

using namespace std;


void solve() {
    int n; cin >> n;
    vector<tuple<int,int,int>> a(n);
    for (int i = 0; i < n; i++) {
        int x,y;
        cin >> x >> y;
        a[i] = {x,y,i};
    }
    sort(a.begin(), a.end(), [&](auto& u, auto& v){
        return get<0>(u) < get<0>(v);
    });
    string res(n, '?');
    char c[2] = {'J', 'C'};
    int r[2] = {};
    for (auto& _: a) {
        int x,y,i;
        tie(x,y,i) = _;
        for (int k:{0,1}) {
            if (r[k] <= x) {
                res[i] = c[k];
                r[k] = y;
                goto nxt;
            }
        }
        cout << "IMPOSSIBLE\n"; return;
        nxt:;
    }
    cout << res << '\n';
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
