#include <bits/stdc++.h>

using namespace std;

void solve() {
    int n; cin >> n;
    if (!(n&1)) {
        cout << "NO"; return;
    }
    vector<int> a(2*n);
    a[0] = 1; a[2*n-1] = 2*n;
    int i = 1, j = n;
    int k = 2;
    while (k < 2*n) {
        a[j] = k; a[j+1] = k+1;
        a[i] = k+2; a[i+1]=k+3;
        i += 2;
        j += 2;
        k += 4;
    }
    cout << "YES\n";
    for (auto& x: a) {
        cout << x << " ";
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
