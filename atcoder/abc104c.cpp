#include <bits/stdc++.h>

using namespace std;


// at most one type not take all.
void solve() {
    int n, g;
    cin >> n >> g;
    g/=100;
    vector<int> p(n), c(n);
    for (int i = 0; i < n; i++) {
        cin >> p[i] >> c[i];
        c[i]/=100;
    }
    const int MSK = 1<<n;
    int res = 1e6;
    for (int msk = 0; msk < MSK; msk++) {
        int sum = 0;
        int cnt = 0;
        for (int i = 0; i < n; i++) {
            if (msk & (1<<i)) {
                sum += p[i]*(i+1) + c[i];
                cnt += p[i];
            }
        }
        if (sum >= g) res = min(res, cnt);
        else {
            for (int i = n-1; i >= 0; i--) {
                if (!(msk & (1<<i))) {
                    for (int j = 0; j < p[i]; j++) {
                        sum += (i+1);
                        cnt += 1;
                        if (sum >= g) res = min(res, cnt);
                    }
                    break;
                }
            }
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
