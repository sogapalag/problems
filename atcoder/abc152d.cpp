#include <bits/stdc++.h>

using namespace std;
using ll=long long;

int cnt[10][10];
void solve() {
    int n; cin >> n;
    for (int i = 1; i <= n; i++) {
        string s = to_string(i);
        cnt[s[0]-'0'][s.back()-'0']++;
    }
    ll res = 0;
    for (int i = 1; i <= n; i++) {
        string s = to_string(i);
        res += cnt[s.back()-'0'][s[0]-'0'];
    }
    cout << res;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}
