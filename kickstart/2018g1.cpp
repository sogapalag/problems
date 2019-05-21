#include <bits/stdc++.h>

using namespace std;


void solve() {
    const int A = 2e5+5; 
    int n; cin >> n;
    vector<int> a(n);
    vector<int> cnt(A, 0);
    for (auto& x: a) {
        cin >> x;
        cnt[x]++;
    }
    long long res = 0;
    sort(a.begin(), a.end());
    int i = cnt[0];
    res += i >= 3? 1ll*i*(i-1)*(i-2)/6 : 0;
    res += i >= 2? 1ll*i*(i-1)/2 * (n-i) : 0;
    int j = cnt[1];
    res += j >= 3? 1ll*j*(j-1)*(j-2)/6 : 0;
    if (j >= 1) {
        for (int k = 2; k < A; k++) {
            res += cnt[k] >= 2? 1ll*j*cnt[k]*(cnt[k]-1)/2 : 0;
        }
    }
    auto it = upper_bound(a.begin(), a.end(), 1);
    for (; it != a.end() && (*it) < 450; it++) {
        for (auto jt = it+1; jt != a.end(); jt++){
            int c = (*it) * (*jt);
            if (c < A && cnt[c]) {
                res += cnt[c];
            }
        }
    }
    cout << res;
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
