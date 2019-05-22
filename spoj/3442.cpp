#include <bits/stdc++.h>

using namespace std;


void solve() {
    vector<vector<int>> d(10);
    d[0] = {0};
    d[1] = {1};
    d[2] = {2, 4, 8, 6};
    d[3] = {3, 9, 7, 1};
    d[4] = {4, 6};
    d[5] = {5};
    d[6] = {6};
    d[7] = {7, 9, 3, 1};
    d[8] = {8, 4, 2, 6};
    d[9] = {9, 1};
    int t; cin >> t;
    while (t--) {
        int a, b;
        cin >> a >> b;
        if (!b) {
            cout << 1 << "\n";
            continue;
        }
        a %= 10;
        int sz = d[a].size();
        b = (b-1) % sz;
        cout << d[a][b] << "\n";
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
