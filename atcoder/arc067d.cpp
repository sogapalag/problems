#include <bits/stdc++.h>

using namespace std;
using ll=long long;

void solve() {
    int n, A,B;
    cin >> n >> A >> B;
    ll res = 0;
    int las; cin >> las;
    for (int _ = 1; _ < n; _++) {
        int x; cin >> x;
        if (1ll*(x-las)*A > B) res += B;
        else res += 1ll*(x-las)*A;
        las = x;
    }
    cout << res;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
