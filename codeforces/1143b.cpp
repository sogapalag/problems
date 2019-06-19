#include <bits/stdc++.h>

using namespace std;

int f(int n) {
    if (n && n < 10) return n;
    if (!n) return 1;
    return max((n%10) * f(n/10), 9 * f(n/10 - 1));
}

void solve() {
    int n; cin >> n;
    int res = f(n);
    cout << res;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
