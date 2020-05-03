#include <bits/stdc++.h>

using namespace std;
using ll=long long;

// rewrite maroon's
// first note optim must some x/d, total O(nD) options
// for fix avg, when we use(fit) some avg|x, imply we can use one less cut
//   how many fit can we have? sort by d=x/avg, #fit = #sum<=D
//     i.e. we greedy put small number, as long as sum not exceed D, imply it's useful fit
void solve() {
    int n, D;
    cin >> n >> D;
    vector<ll> a(n);
    for (auto& x: a) cin >> x;
    sort(a.begin(), a.end(), greater<ll>());
    int res = D-1;
    // wlog x1/p1 = x2/p2 =...=x/p
    // note when we multiply some _ = p imply p|xp, and then x1_ / p1 = x'/d= x i.e. d|x'
    // thus we can ignore frac, operate integer directly. can another method too.
    for (int _ = 1; _ <= D; _++) {
        auto b = a;
        for (auto& x: b) {
            x *= _;
        }
        vector<pair<ll,int>> perfect;
        for (auto& x: b) {
            for (int d = 1; d <= D; d++) {
                if (x%d == 0) perfect.emplace_back(x/d, d);
            }
        }
        sort(perfect.begin(), perfect.end());
        int m = perfect.size();
        int i = 0, j = 0;
        while (i < m) {
            int sum = 0, fit = 0;
            while (j < m && perfect[j].first == perfect[i].first) {
                sum += perfect[j].second;
                if (sum <= D) fit++;
                ++j;
            }
            ll val = perfect[i].first;
            ll has = 0;
            // check we indeed has >=D within not perfect too
            for (auto& x: b) {
                ll could = x/val;
                if (could == 0) break; // early stop
                has += could;
                if (has >= D) break;
            }
            if (has >= D) res = min(res, D - fit);
            i = j;
        }
    }
    cout << res << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int T; cin >> T;
    for (int t = 1; t <= T; t++) {
        cout << "Case #" << t << ": ";
        solve();
    }
    return 0;
}
