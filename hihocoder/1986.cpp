#include <bits/stdc++.h>

using namespace std;


void solve() {
    int n; cin >> n;
    vector<int> cnt(1000006, 0);
    for (int _ = 0; _ < n; _++) {
        int x; cin >> x;
        cnt[x]++;
    }
    vector<int> a;
    for (int x: cnt) {
        if (x) a.emplace_back(x);
    }
    sort(a.begin(), a.end(), greater<int>());
    int m = a.size();
    int res = 0;
    for (int i = 1; i < m; i++) {
        if (a[i] >= a[i-1]) {
            int nex = max(0, a[i-1]-1);
            res += a[i] - nex;
            a[i] = nex;
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
