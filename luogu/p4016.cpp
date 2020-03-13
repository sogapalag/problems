#include <bits/stdc++.h>

using namespace std;
using ll=long long;

// 网络流24题 负载平衡问题
// it's easy to note for avg[..], if non-cycle, res:= cut = sum |pref|
// then for cycle, note 0,n-1 can transport any x, then f(x) = sum |pref-x| + |x|
// i.e. n points, x as mid, reach min-cost
void solve() {
    int n; cin >> n;
    vector<ll> a(n);
    ll sum = 0;
    for (auto& x: a) {
        cin >> x;
        sum += x;
    }
    ll avg = sum/n;
    assert(avg*n == sum);
    for (auto& x: a) {
        x -= avg;
    }
    vector<ll> b;
    b.push_back(0);
    sum = 0;
    for (int i = 0; i < n-1; i++) {
        sum += a[i];
        b.push_back(sum);
    }
    sort(b.begin(), b.end());
    sum = 0;
    for (int i = 0; i < n-i; i++) {
        sum += b[n-i-1] - b[i];
    }
    cout << sum;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}
