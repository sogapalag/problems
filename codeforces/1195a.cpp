#include <bits/stdc++.h>

using namespace std;


void solve() {
    int n, k;
    cin >> n >> k;
    vector<int> cnt(k+1, 0);
    for (int _ = 0; _ < n; _++) {
        int x; cin >> x;
        cnt[x]++;
    }
    int sat = 0;
    int rem = 0;
    for (int i = 1; i <= k; i++) {
        sat += cnt[i]/2 *2;
        rem += (cnt[i] & 1);
    }
    int res = sat + (rem+1)/2;
    cout << res;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
