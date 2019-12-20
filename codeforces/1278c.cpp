#include <bits/stdc++.h>

using namespace std;


void solve() {
    int n; cin >> n;
    vector<int> a(n+1), b(n+1);
    for (int i = 1; i <= n; i++) {
        int x; cin >> x;
        x = (x==1?1:-1);
        a[i] = a[i-1] + x;
    }
    for (int i = n; i >= 1; i--) {
        int x; cin >> x;
        x = (x==1?-1:1);
        b[i] = x;
    }
    for (int i = 1; i <= n; i++) {
        b[i] += b[i-1];
    }
    unordered_map<int, int> A, B;
    for (int i = 0; i <= n; i++) {
        A[a[i]] = i;
        B[b[i]] = i;
    }
    int res = 2*n;
    for (int i = 0; i <= n; i++) {
        int x = a[i];
        if (B.find(x)!=B.end()) {
            res = min(res, n-i + n-B[x]);
        }
    }
    cout << res << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int t; cin >> t;
    while(t--)solve();
    cout << endl;
}
