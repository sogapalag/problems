#include <bits/stdc++.h>

using namespace std;


void solve() {
    int n, l;
    cin >> n >> l;
    vector<int> a(n+1);
    int mi = 1e8;
    int c = -1;
    int sum = 0;
    for (int i = 1; i <= n; i++) {
        a[i] = l+i-1;
        sum += a[i];
        if (abs(a[i]) < mi) {
            mi = abs(a[i]);
            c = a[i];
        }
    }
    cout << sum - c;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
