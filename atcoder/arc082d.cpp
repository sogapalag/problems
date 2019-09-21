#include <bits/stdc++.h>

using namespace std;


void solve() {
    int n; cin >> n;
    vector<int> a(n);
    for (auto& x: a) {
        cin >> x;
        x--;
    }
    int res = 0;
    for (int i = 0; i < n; i++) {
        // always swap next, since next!=i, so no contradiction. when end, atctually swap n-2. but ++ fine
        if (a[i] == i) {
            res++;
            i++;
        }
    }
    cout << res;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
