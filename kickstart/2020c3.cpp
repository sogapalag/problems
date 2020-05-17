#include <bits/stdc++.h>

using namespace std;
using ll=long long;
const int N = 1e7+100; 
const int B = 1e7+10; 
int __cnt[N<<1];
int* cnt = __cnt+N;
// 10*n^1.5
void solve() {
    int n; cin >> n;
    vector<int> a(n);
    for (auto& x: a) cin >> x;
    vector<int> sum(n + 1);
    ++cnt[0];
    int LIM = 0;
    while (LIM*LIM <= n*100) LIM++;
    ll res = 0;
    for (int i = 0; i < n; i++) {
        sum[i+1] = sum[i] + a[i];
        int x = sum[i+1];
        for (int k = 0; k < LIM && x-k*k > -B; k++) {
            res += cnt[x-k*k];
        }
        ++cnt[x];
    }
    for (int x: sum) --cnt[x];
    cout << res << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    memset(__cnt, 0, sizeof __cnt);
    int T; cin >> T;
    for (int t = 1; t <= T; t++) {
        cout << "Case #" << t << ": ";
        solve();
    }
    return 0;
}
