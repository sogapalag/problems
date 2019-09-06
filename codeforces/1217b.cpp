#include <bits/stdc++.h>

using namespace std;


void solve() {
    int n, X;
    cin >> n >> X;
    int u=0, v=0;
    for (int _ = 0; _ < n; _++) {
        int x,y;
        cin >> x >> y;
        u=max(u,x);
        v=max(v,x-y);
    }
    if (u >= X) {
        cout << "1\n"; return;
    }
    if (v <= 0) {
        cout << "-1\n"; return;
    }
    int res = (X-u+v-1)/(v) + 1;
    cout << res << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int t; cin >> t;
    while(t--)solve();
    cout << endl;
}
