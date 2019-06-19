#include <bits/stdc++.h>

using namespace std;


void solve() {
    int n; cin >> n;
    vector<int> a(n);
    for (auto& x: a) {
        cin >> x;
    }
    reverse(a.begin(), a.end());
    int i = 0;
    while (i < n && a[i] == a[0]) {
        i++;
    }
    cout << (n - i);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
