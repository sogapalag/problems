#include <bits/stdc++.h>

using namespace std;


void solve() {
    int n; cin >> n;
    vector<int> deg(n, 0);
    for (int i = 1; i < n; i++) {
        int x, y;
        cin >> x >> y;
        x--; y--;
        deg[x]++; deg[y]++;
    }
    for (auto& x: deg) {
        if (x == 2) {
            cout << "NO"; return;
        }
    }
    cout << "YES";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
