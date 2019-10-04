#include <bits/stdc++.h>

using namespace std;


void solve() {
    string s; cin >> s;
    int cnt = 0;
    for (char c: s) if (c=='p') cnt++;
    int res = (int)s.size()/2 - cnt;
    cout << res;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
