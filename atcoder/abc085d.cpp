#include <bits/stdc++.h>

using namespace std;


void solve() {
    int n, H;
    cin >> n >> H;
    vector<int> a(n), b(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i] >> b[i];
    }
    int keep = *max_element(a.begin(), a.end());
    sort(b.begin(), b.end(), greater<int>());
    long long once=0;
    int cnt = 0;
    for (int x: b) {
        if (x <= keep) break;
        once += x;
        cnt++;
        if (once >= H) {
            cout << cnt; return;
        }
    }
    int res = cnt + (H-once+keep-1)/keep;
    cout << res;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
