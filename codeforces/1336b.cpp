#include <bits/stdc++.h>

using namespace std;
using ll=long long;
vector<vector<int>> perm;
void solve() {
    int n[3];
    for (int i = 0; i < 3; i++) {
        cin >> n[i];
    }
    vector<vector<int>> a(3);
    for (int i = 0; i < 3; i++) {
        for (int _ = 0; _ < n[i]; _++) {
            int x; cin >> x;
            a[i].push_back(x);
        }
        sort(a[i].begin(), a[i].end());
    }
    ll res = 1ll<<61;
    for (auto& p: perm) {
        int i = p[0], j = p[1], k = p[2];
        // x<=y<=z
        for (int y: a[j]) {
            int ii = upper_bound(a[i].begin(), a[i].end(), y) - a[i].begin();
            int kk = lower_bound(a[k].begin(), a[k].end(), y) - a[k].begin();
            if (ii>0 && kk < n[k]) {
                int x = a[i][ii-1];
                int z = a[k][kk];
                ll tmp = (x-y)*1ll*(x-y) + (y-z)*1ll*(y-z) + (x-z)*1ll*(x-z);
                res = min(res, tmp);
            }
        }
    }
    cout << res << "\n";
}

int main() {
    vector<int> p(3);
    iota(p.begin(), p.end(), 0);
    do {
        perm.push_back(p);
    } while (next_permutation(p.begin(), p.end()));
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int T; cin >> T;
    for (int t = 0; t < T; t++) {
        solve();
    }
    return 0;
}
