#include <bits/stdc++.h>

using namespace std;
using ll=long long ;
const int L = 61; 

// i,j in N, not in B. read problem carefully!!
//
// for x in B, color pattern.
// 0   1   0   1   0  1 ....
//    +x  +2x +3x +4x +5x ...
// so ax = by, a.b parity cannot differ,
//   thus all B has same e, x = 2^e*u
void solve() {
    int n; cin >> n;
    vector<ll> a[L];
    vector<int> cnt(L, 0);
    for (int _ = 0; _ < n; _++) {
        ll x; cin >> x;
        int e = 0;
        ll y = x;
        while (x % 2 == 0) {
            x /= 2; e++;
        }
        a[e].emplace_back(y);
        cnt[e]++;
    }
    int i = max_element(cnt.begin(), cnt.end()) - cnt.begin();
    int res = n - cnt[i];
    cout << res << "\n";
    for (int j = 0; j < L; j++) {
        if (j != i) {
            for (auto& x: a[j]) {
                cout << x << ' ';
            }
        }
    }

}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
