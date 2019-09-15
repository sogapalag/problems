#include <bits/stdc++.h>

using namespace std;


// for mini disjoint seg, |..1,2..,2,1|, which contain all number in the seg
// len - mx_cnt is ans to the seg. so res = sum ans
void solve() {
    int n, q;
    cin >> n >> q;
    vector<int> a(n);
    vector<int> cnt(200005, 0);
    vector<int> R(200005, -1);
    for (int i = 0; i < n; i++) {
        int x; cin >> x;
        cnt[x]++;
        R[x] = i;
        a[i] = x;
    }
    int rx = -1;
    int len = 0;
    int mx_cnt = 0;
    int res = 0;
    for (int i = 0; i < n; i++) {
        int x = a[i];
        rx = max(rx, R[x]);
        mx_cnt = max(mx_cnt, cnt[x]);
        len++;
        if (i == rx) {
            res += len - mx_cnt;
            len = 0; mx_cnt = 0;
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
