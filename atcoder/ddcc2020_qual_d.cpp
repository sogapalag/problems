#include <bits/stdc++.h>

using namespace std;
using ll=long long;

// key observation: no matter order of chosing.
// let m be #digits
// each step, either m -1 or sum -9
void solve() {
    int n; cin >> n;
    ll sum = 0;
    ll m = 0;
    for (int _ = 0; _ < n; _++) {
        int d; ll c;
        cin >> d >> c;
        sum += d * c;
        m += c;
    }
    ll res = (sum-1)/9 + (m-1);
    cout << res;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
