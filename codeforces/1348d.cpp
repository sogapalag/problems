#include <bits/stdc++.h>

using namespace std;


// editorial much elegant
// add all delta, 1, 2, 4,.. x
// then sort, ans are d(delta)
void solve() {
    int n; cin >> n;
    n--;
    vector<int> res;
    int x = 1;
    while (n > 0) {
        if (n >= 4*x) {
            res.push_back(x);
            x *= 2;
        } else if (n > 2*x) {
            res.push_back(n/2 - x);
            x = n/2;
        } else {
            res.push_back(n - x);
            x = n;
        }
        n -= x;
    }
    cout << res.size() << "\n";
    for (auto& x: res) {
        cout << x << ' ';
    }cout << '\n';
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int T; cin >> T;
    for (int t = 0; t < T; t++) {
        solve();
    }
    return 0;
}
