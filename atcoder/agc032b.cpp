#include <bits/stdc++.h>

using namespace std;


// wlog n even.
// (1,n) (2,n-1),.. 's complement graph.
void solve() {
    int n; cin >> n;
    int m = n - (n&1);
    vector<pair<int, int>> res;
    for (int i = 1; i <= n; i++) {
        for (int j = i+1; j <= n; j++) {
            if (i+j != m+1) {
                res.emplace_back(i, j);
            }
        }
    }
    cout << res.size() << "\n";
    int x, y;
    for (auto& p: res) {
        tie(x,y) = p;
        cout << x << ' ' << y << "\n";
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
