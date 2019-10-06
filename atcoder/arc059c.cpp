#include <bits/stdc++.h>

using namespace std;


void solve() {
    int n; cin >> n;
    vector<int> a(n);
    for (auto& x: a) {
        cin >> x;
    }
    int res = 1<<30;
    for (int k = -100; k <= 100; k++) {
        int sum = 0;
        for (int x: a) sum += (x-k)*(x-k);
        res = min(res, sum);
    }
    cout << res;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
