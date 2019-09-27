#include <bits/stdc++.h>

using namespace std;
using ll=long long;

void solve() {
    int n; ll K;
    cin >> n >> K;
    vector<pair<int, int>> a(n);
    for (auto& p: a) {
        cin >> p.first >> p.second;
    }
    sort(a.begin(), a.end());
    vector<ll> sum(n+1);
    sum[0] = 0;
    for (int i = 1; i <= n; i++) {
        sum[i] = sum[i-1] + a[i-1].second;
    }
    
    int i = lower_bound(sum.begin(), sum.end(), K) - sum.begin();
    cout << a[i-1].first;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
