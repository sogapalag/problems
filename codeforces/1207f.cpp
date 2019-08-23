#include <bits/stdc++.h>

using namespace std;

const int N = 500'000; 
const int S = 700;
int a[N+1];
int sum[S+1][S];

void solve() {
    int q;cin >> q;int res;
    while (q--) {
        int k,x,y;
        cin >> k >> x >> y;
        if (k == 1) {
            a[x] += y;
            for (int i = 1; i <= S; i++) {
                sum[i][x%i] += y;
            }
        } else {
            if (x <= S) {
                res = sum[x][y];
            } else {
                res = 0;
                for (int i = y; i <= N; i+=x) {
                    res += a[i];
                }
            }
            cout << res << "\n";
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
