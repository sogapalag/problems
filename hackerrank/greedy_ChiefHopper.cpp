#include <bits/stdc++.h>

using namespace std;


// time-reversal at least pass.
// although a dummy solution can just bs then in-time check
void solve() {
    int n; cin >> n;
    vector<int> a(n);
    for (auto& x: a) {
        cin >> x;
    }
    reverse(a.begin(), a.end());
    int res = 0;
    for (auto& x: a) {
        res = (res + x + 1)/2;
    }
    cout << res;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
