#include <bits/stdc++.h>

using namespace std;


void solve() {
    int n; cin >> n;
    long long res = 0;
    int rem = 0;
    for (int _ = 0; _ < n; _++) {
        int x; cin >> x;
        int k = min(x/2, rem);
        res += k;  rem -= k;  x -= 2*k;
        res += x/3; rem += x%3;
    }
    cout << res;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
