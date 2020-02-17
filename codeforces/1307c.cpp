#include <bits/stdc++.h>

using namespace std;
using ll=long long;
int cnt[26];
ll a[26][26];
// only len=1 or 2, be candidate, since #(>=3) sub #2, imply by +d +2d +3d
// and len 2, must be prog-arith
void solve() {
    string s; cin >> s;
    for (char c:s){
        int x = c-'a';
        for (int i = 0; i < 26; i++) {
            a[i][x] += cnt[i];
        }
        cnt[x]++;
    }
    ll res = *max_element(cnt, cnt+26);
    for (int i = 0; i < 26; i++) {
        for (int j = 0; j < 26; j++) {
            res = max(res, a[i][j]);
        }
    }
    cout << res;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}
