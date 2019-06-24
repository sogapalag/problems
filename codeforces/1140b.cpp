#include <bits/stdc++.h>

using namespace std;


void solve() {
    int n; cin >> n;
    string s; cin >> s;
    if (s[0]=='>' || s[n-1] =='<'){
        cout << 0 << "\n";
        return;
    }
    int res = n;
    int i=0;
    while (i<n && s[i]=='<') {
        i++;
    }
    res = min(res, i);
    i = n-1;
    while (i>=0 && s[i]=='>') {
        i--;
    }
    res = min(res, n-1-i);
    cout << res << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int t; cin >> t;
    while(t--) solve();
    cout << endl;
}
