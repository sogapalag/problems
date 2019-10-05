#include <bits/stdc++.h>

using namespace std;

using ll=long long;
void solve() {
    string s; cin >> s;
    reverse(s.begin(), s.end());
    int n = s.size();
    ll res = 0;
    for (int i = 0; i < n; i++) {
        ll x = s[i]-'0';
        for (int j = 0; j < i; j++) {
            res += x * pow(10, j) * (1<<(n-2-j));
        }
        res += x * pow(10, i) * (1<<(n-1-i));
    }
    cout << res;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
