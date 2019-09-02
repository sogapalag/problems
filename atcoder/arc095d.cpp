#include <bits/stdc++.h>

using namespace std;


void solve() {
    int n; cin >> n;
    vector<int> a(n);
    for (auto& x: a) {
        cin >> x;
    }
    sort(a.begin(), a.end());
    int N = a[n-1];
    int i = lower_bound(a.begin(), a.end(), a[n-1]/2) - a.begin();
    if (i==n-1) i--;
    int K = a[i];
    if (i && N-a[i-1]<K)
        K = a[i-1];
    cout << N << ' ' << K;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
