#include <bits/stdc++.h>

using namespace std;


void solve() {
    int n;
    cin >> n;
    vector<int> a(n+1);
    a[1] = 1;
    for (int i = 1; i < n; i++) {
        a[i+1] = a[i] + 4*i;
    }
    cout << a[n];
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
