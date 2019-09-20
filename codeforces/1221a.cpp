#include <bits/stdc++.h>

using namespace std;

int cnt[30];

void solve() {
    int n; cin >> n;
    memset(cnt, 0, sizeof cnt);
    for (int _ = 0; _ < n; _++) {
        int x; cin >> x;
        if (x > 2048) continue;
        cnt[__builtin_ctz(x)]++;
    }
    for (int i = 0; i <= 10; i++) {
        cnt[i+1] += cnt[i]/2;
    }
    auto res = cnt[11]>0?"YES\n":"NO\n";
    cout << res;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int t; cin >> t;
    while(t--)solve();
    cout << endl;
}
