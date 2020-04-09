#include <bits/stdc++.h>

using namespace std;


// for b|a, b<a, if only one in M, it's always choose b.
// => if a in M, \A d|a in M too.
// => gcd(.,a) = max d, (d|a,d<a)
// => gcd(M) = max_a gcd(.,a) = max d
void solve() {
    int n; cin >> n;
    vector<int> a(n + 1);
    for (int i = 1; i <= n; i++) {
        for (int j = i; (j+=i) <= n;) {
            a[j] = i;
        }
    }
    sort(a.begin(), a.end());
    for (int i = 2; i <= n; i++) {
        cout << a[i] << ' ';
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}
