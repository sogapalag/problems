#include <bits/stdc++.h>

using namespace std;


//void solve() {
//    int n,m,q;
//    cin >> n >> m >> q;
//    int sq = n < 50000 ? 300 : 400;
//    vector<int> a(n+1, 0);
//    vector<int> cnt(sq, 0);  
//    for (int _ = 0; _ < m; _++) {
//        int x; cin >> x;
//        a[x]++;
//        for (int i = 1; i < sq; i++) {
//            if (x % i == 0) cnt[i]++;
//        }
//    }
//    long long res = 0;
//    while (q--) {
//        int x; cin >> x;
//        if (x < sq) {
//            res += n/x - cnt[x];
//        } else {
//            for (int i = x; i <= n; i+=x) {
//                res += a[i]^1;
//            }
//        }
//    }
//    cout << res;
//}
// no need. simple n log n


void solve() {
    int n,m,q;
    cin >> n >> m >> q;
    vector<int> a(n+1);
    fill(a.begin(), a.end(), 1);
    for (int _ = 0; _ < m; _++) {
        int x; cin >> x;
        a[x] = 0;
    }
    vector<int> res(n+1);
    for (int i = 1; i <= n; i++) {
        for (int j = i; j <= n; j+=i) {
            res[i] += a[j];
        }
    }
    long long sum = 0;
    while (q--) {
        int x; cin >> x;
        sum += res[x];
    }
    cout << sum;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int T; cin >> T;
    for (int t = 1; t <= T; t++) {
        cout << "Case #" << t << ": ";
        solve();
        cout << "\n";
    }
    fflush(stdout);
}
