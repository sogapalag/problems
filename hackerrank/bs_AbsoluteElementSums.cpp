#include <bits/stdc++.h>

using namespace std;


void solve() {
    int n; cin >> n;
    vector<int> a(n);
    for (auto& x: a) {
        cin >> x;
    }
    sort(a.begin(), a.end());
    vector<int> sum(n);
    int tmp = 0;
    for (int i = 0; i < n; i++) {
        sum[i] = (tmp+=a[i]);
    }
    int q; cin >> q;
    vector<int> d(q);
    tmp = 0;
    for (int i = 0; i < q; i++) {
        int x; cin >> x;
        d[i] = (tmp+=x);
    }
    for (int i = 0; i < q; i++) {
        int j = lower_bound(a.begin(), a.end(), -d[i]) - a.begin();
        long long res = sum[n-1] - (j>0 ? 2*sum[j-1]: 0);
        res += (long long)(n-j - j) * d[i];
        cout << res << "\n";
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
