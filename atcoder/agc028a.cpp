#include <bits/stdc++.h>

using namespace std;


void solve() {
    int n,m;
    cin >> n >> m;
    string s,t;
    cin >> s >> t;
    int g = __gcd(n,m);
    int a = n/g, b = m/g;
    for (int i=0,j=0; i<n && j<m; i+=a, j+=b) {
        if (s[i] != t[j]) {
            cout << -1; return;
        }
    }
    long long res = 1ll*n*m/g;
    cout << res;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
