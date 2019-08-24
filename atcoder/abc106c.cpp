#include <bits/stdc++.h>

using namespace std;

using ll=long long ;
void solve() {
    string s; cin >> s;
    ll k; cin >> k;
    int i = 0;
    while (s[i]=='1') {
        i++;
    }
    char res = k <= i? '1' : s[i];
    cout << res;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
