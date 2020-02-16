#include <bits/stdc++.h>

using namespace std;
using ll=long long;

void solve() {
    int n; cin >> n;
    vector<int> stk;
    ll res = 0;
    for (int _ = 0; _ < n; _++) {
        int x; cin >> x;
        while (stk.size() >= 2) {
            int m = stk.size();
            // editorial pick global min, while local minimum is sufficient
            // since it won't make its adj worse. and possible left-larger contribute to i or i-1 is same.
            if (stk[m-2] >= stk[m-1] && stk[m-1] <= x) {
                res += min(stk[m-2], x);
                stk.pop_back();
            } else break;
        }
        stk.push_back(x);
    }
    sort(stk.begin(), stk.end());
    int m = stk.size();
    for (int i = 0; i < m-2; i++) {
        res += stk[i];
    }
    cout << res;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}
