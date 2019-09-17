#include <bits/stdc++.h>

using namespace std;


void solve() {
    int n,k;
    cin >> n >> k;
    vector<pair<int, int>> a(n);
    vector<int> X(n), Y(n);
    for (int i = 0; i < n; i++) {
        cin >> X[i] >> Y[i];
        a[i] = {X[i], Y[i]};
    }
    sort(X.begin(), X.end());
    sort(Y.begin(), Y.end());
    long long res = 1ll<<62;
    for (int i = 0; i < n; i++) {
        for (int j = i; j < n; j++) {
            for (int s = 0; s < n; s++) {
                for (int t = s; t < n; t++) {
                    int x[2] = {X[i], X[j]};
                    int y[2] = {Y[s], Y[t]};
                    int cnt = 0;
                    for (auto& p: a) {
                        if (x[0]<=p.first&&p.first<=x[1] && y[0]<=p.second&&p.second<=y[1])cnt++;
                    }
                    if (cnt>=k) res = min(res, 1ll*(x[1]-x[0])*(y[1]-y[0]));
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
