#include <bits/stdc++.h>

using namespace std;

//const int N = 3003;
//int dp[2][N];
//
//// max as end, WA
//void solve() {
//    int n, T;
//    cin >> n >> T;
//    vector<int> a(n), b(n);
//    int mx = 0, mi = N, id = -1;
//    for (int i = 0; i < n; i++) {
//        cin >> a[i] >> b[i];
//        if (b[i] > mx || (b[i] == mx && a[i] < mi)) {
//            mx = b[i];
//            mi = a[i];
//            id = i;
//        }
//    }
//    for (int i = 0; i < n; i++) {
//        if (i == id) continue;
//        int x = a[i], y = b[i];
//        for (int t = N-1; t >= 0; t--) {
//            dp[1][t] = max({dp[1][t], t>=x?dp[1][t-x]+y:0, t>=min(x,mi)?dp[0][t-min(x,mi)]:0});
//        }
//        for (int t = N-1; t >= 0; t--) {
//            dp[0][t] = max(dp[0][t], t>=x?dp[0][t-x]+y:0);
//        }
//    }
//    int res = max(dp[0][T-1], dp[1][T-1]) + mx;
//    cout << res;
//}

const int N = 3003; 
int dp[N][N], back[N][N];

// optim structure, some i as end.
// trivial O(N^3), trick, split two part, hence O(N^2)
void solve() {
    int n, T;
    cin >> n >> T;
    vector<int> a(n), b(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i] >> b[i];
    }
    for (int i = 0; i < n; i++) {
        int x = a[i], y = b[i];
        for (int t = 0; t < N; t++) {
            dp[i+1][t] = dp[i][t];
            if (t >= x) dp[i+1][t] = max(dp[i+1][t], dp[i][t-x] + y);
            if (t) dp[i+1][t] = max(dp[i+1][t], dp[i+1][t-1]); // pref-max on t
        }
    }
    for (int i = n-1; i >= 0; i--) {
        int x = a[i], y = b[i];
        for (int t = 0; t < N; t++) {
            back[i][t] = back[i+1][t];
            if (t >= x) back[i][t] = max(back[i][t], back[i+1][t-x] + y);
            if (t) back[i][t] = max(back[i][t], back[i][t-1]); // pre-max on t
        }
    }
    int res = 0;
    // i as end, iter first part in j
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < T; j++) {
            int tmp = dp[i][j] + back[i+1][T-1-j] + b[i];
            res = max(res, tmp);
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
