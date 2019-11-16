#include <bits/stdc++.h>

using namespace std;


void solve() {
    string s; cin >> s;
    long long res = 0;
    int cnt = 0;
    for (char c: s) {
        if (c == 'B') cnt++;
        else res += cnt;
    }
    cout << res;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
