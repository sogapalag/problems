#include <bits/stdc++.h>

using namespace std;
using ll=long long;

void solve() {
    int n,s;
    cin >> n >> s;
    vector<int> a(n);
    for (auto& x: a) {
        cin >> x;
    }
    ll sum = 0;
    int mx = 0, id = 0;
    for (int i = 0; i < n; i++) {
        sum += a[i];
        if (a[i]>mx) {
            mx = a[i];
            id = i+1;
        }
        if (sum > s) {
            cout << id << "\n";
            return;
        }
    }
    cout << 0 << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int t;cin >> t;
    while(t--)solve();
    cout << endl;
}
