#include <bits/stdc++.h>

using namespace std;

const int N = 512; 
int dp[N];

// O(n^2)
// note greedy match i..j may not optimal for i..j
// but it along with dp[i] + i..j, which must cover a optim.
//  since optim-form is some disjoint could-collapse-segment
void solve() {
    int n; cin >> n;
    vector<int> a(n);
    for (auto& x: a) {
        cin >> x;
    }
    memset(dp, 0x3f, sizeof dp);
    dp[0] = 0;
    for (int i = 0; i < n; i++) {
        vector<int> stk;
        for (int j = i; j < n; j++) {
            stk.push_back(a[j]);
            while (stk.size() >= 2) {
                int m = stk.size();
                if (stk[m-2] != stk[m-1]) break;
                stk[m-2]++; stk.pop_back();
            }
            dp[j + 1] = min(dp[j + 1], dp[i] + (int)stk.size());
        }
    }
    cout << dp[n];
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}
