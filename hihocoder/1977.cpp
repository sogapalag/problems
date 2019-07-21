#include <bits/stdc++.h>

using namespace std;


void solve() {
    int n; cin >> n;
    vector<int> a(n);
    for (auto& x: a) {
        cin >> x;
    }
    sort(a.begin(), a.end());
    int i = 0;
    int las = 0;
    while (i < n && a[i] - las <= 1) {
        las = a[i];
        i++;
    }
    cout << i;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
