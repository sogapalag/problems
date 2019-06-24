#include <bits/stdc++.h>

using namespace std;


void solve() {
    int n; cin >> n;
    vector<int> a(n);
    for (auto& x: a) {
        cin >> x;
    }
    reverse(a.begin(), a.end());
    int mi = 1<<30;
    long long res = 0;
    for (int i = 0; i < n; i++) {
        mi = min(mi, a[i]);
        res += mi;
        if (mi) mi--;
    }
    cout << res;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
