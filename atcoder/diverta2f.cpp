#include <bits/stdc++.h>

using namespace std;

using ll=long long;
ll w[12][12];

void solve() {
    int n; cin >> n;
    // a_i, a_i + a_j differ
    vector<int> a = {1, 2, 4, 7, 12, 20, 29, 38, 52, 73};
    memset(w, 0, sizeof w);
    w[1][0] = w[0][1] = 1;
    ll M = 1;
    auto upd = [&](int x){
        vector<int> v(x);
        iota(v.begin(), v.end(), 0);
        ll mx = 0;
        do {
            ll sum = 0;
            for (int i = 1; i < x; i++) {
                sum += w[v[i-1]][v[i]];
            }
            mx = max(mx, sum);
        } while (next_permutation(v.begin(), v.end()));
        M = mx;
    };
    for (int i = 2; i < n; i++) {
        for (int j = 0; j < i; j++) {
            w[i][j] = w[j][i] = (M+1) * a[j];
        }
        upd(i+1);
        //cout << M << ' ';
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cout << w[i][j] << ' ';
        }
        cout << "\n";
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
