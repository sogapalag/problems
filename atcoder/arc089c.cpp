#include <bits/stdc++.h>

using namespace std;


void solve() {
    int n; cin >> n;
    int ct=0, cx=0, cy=0;
    for (int _ = 0; _ < n; _++) {
        int t,x,y;
        cin >> t >> x >> y;
        int d = abs(x-cx) + abs(y-cy);
        int dt = t - ct;
        if (dt>=d && (dt-d)%2==0) {
            ct=t, cx=x, cy=y;
        } else {
            cout << "No"; return;
        }
    }
    cout << "Yes";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
