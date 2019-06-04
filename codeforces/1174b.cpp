#include <bits/stdc++.h>

using namespace std;


void solve() {
    int n; cin >> n;
    vector<int> a(n);
    int odd=0, even=0;
    for (auto& x: a) {
        cin >> x;
        odd += (x & 1);
        even += !(x&1);
    }
    if (odd && even) {
        sort(a.begin(), a.end());
    }
    for (auto& x: a) {
        cout << x << ' ';
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
