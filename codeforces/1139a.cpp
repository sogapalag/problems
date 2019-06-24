#include <bits/stdc++.h>

using namespace std;


void solve() {
    int n;
    cin >> n;
    string s;
    cin >> s;
    reverse(s.begin(), s.end());
    long long  res = 0;
    for (int i = 0; i < n; i++) {
        int x = s[i] - '0';
        if (x%2 == 0) res += (n-i);
    }
    cout << res;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
