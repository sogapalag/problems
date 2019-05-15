#include <bits/stdc++.h>

using namespace std;
const long long MOD = 998244353;
    
void solve() {
	int n; cin >> n;
    vector<long long> a(n);

    for (long long i = 0; i < n; i++) {
        cin >> a[i];
        a[i] *= (i+1) * (n-i);
    }
    vector<long long> b(n);
    for (int i = 0; i < n; i++) {
        cin >> b[i];
    }
    sort(a.begin(), a.end());
    sort(b.begin(), b.end(), greater<long long>());
    long long res = 0;
    for (int i = 0; i < n; i++) {
        long long tmp = (a[i] % MOD) * b[i] % MOD;
        res += tmp;
        res %= MOD;
    }
    cout << res;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
