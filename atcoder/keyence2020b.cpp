#include <bits/stdc++.h>

using namespace std;


void solve() {
    int n; cin >> n;
    vector<pair<int, int>> a(n);
    for (int i = 0; i < n; i++) {
        int x,l;
        cin >> x >> l;
        a[i] = {x+l, x-l};
    }
    sort(a.begin(), a.end());
    int cnt = 1;
    int r = a[0].first;
    for (int i = 1; i < n; i++) {
        if (a[i].second < r) continue;
        cnt++;
        r = a[i].first;
    }
    cout << cnt;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}
