#include <bits/stdc++.h>

using namespace std;

// has bs property, smaller are not necessary. i.e. once x nec., >= x also nec. so cnt reset =0. 
//    and if x indeed nec. some less y will reset it.
void solve() {
    int n,k;
    cin >> n >> k;
    vector<int> a(n);
    for (auto& x: a) {
        cin >> x;
    }
    sort(a.begin(), a.end(), greater<int>());
    bitset<5000> dp;
    dp[0] = 1;
    int cnt = 0;
    for (int x: a) {
        bool nec = false;
        for (int i = k-1; i >= 0; i--) {
            if (dp[i]) {
                if (x+i >= k) nec = true;
                else dp[x+i] = 1;
            }
        }
        if (nec) cnt = 0;
        else cnt++;
    }
    cout << cnt;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
