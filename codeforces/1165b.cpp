#include <bits/stdc++.h>

using namespace std;


void solve() {
    int n; cin >> n;
    vector<int> a(n);
    for (auto& x: a) {
        cin >> x;
    }
    sort(a.begin(), a.end());
    auto it = a.begin();
    int k;
    for (k = 1; k <= n; k++) {
        it = lower_bound(it, a.end(), k);
        if (it == a.end()) break;
        it++;
    }
    k--;
    cout << k;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
