#include <bits/stdc++.h>

using namespace std;


void solve() {
    int n, t;
    cin >> n >> t;
    vector<int> a(n+1);
    for (int i = 1; i <= n; i++) {
        int s, d;
        cin >> s >> d;
        a[i] = s < t? (t-s+d-1)/d * d + s : s;
    }
    int res = 1, crt =  1e7;
    for (int i = 1; i <= n; i++) {
        if (a[i] < crt) {
            res = i;
            crt = a[i];
        }
    }
    cout << res;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
