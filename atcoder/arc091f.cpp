#include <bits/stdc++.h>

using namespace std;
// mex
// 0 1 2 ... k k+1 .. 2k..
// 0 0 0 ..0 1 0 .... 2..
// also, seq - {s_0,s_k,s_2k,...} = seq
int sg(int n, int k) {
    if (n%k == 0) return n/k;
    int t = n/k + 1;
    return sg(n - (n%k +t-1)/t *t, k);
}

void solve() {
    int n;cin >> n;
    int res = 0;
    for (int _ = 0; _ < n; _++) {
        int x,y;
        cin >> x >> y;
        res ^= sg(x,y);
    }
    cout << (res?"Takahashi":"Aoki");
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
