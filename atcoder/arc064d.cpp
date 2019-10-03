#include <bits/stdc++.h>

using namespace std;

// don't care operation,
// final must be ababa or abab
void solve() {
    string s; cin >> s;
    int n = s.size();
    int x = n&1;
    int y = s[0] == s[n-1];
    auto res = (x^y)?"First":"Second";
    cout << res;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
