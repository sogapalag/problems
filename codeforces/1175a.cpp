#include <bits/stdc++.h>

using namespace std;

long long f(long long n, long long k) {
    if (n < k) {
        return n;
    }
    return 1 + (n%k) +f(n/k, k);
}

void solve() {
    int t; cin >> t;
    while (t--) {
        long long n, k;
        cin >> n >> k;
        cout << f(n,k) << "\n";
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
