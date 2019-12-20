#include <bits/stdc++.h>

using namespace std;


void solve() {
    string s,t;
    cin >> s >> t;
    vector<int> a(26,0), b(26,0);
    for (char c:s)a[c-'a']++;
    int n = s.size(), m = t.size();
    bool yes = false;
    if (n <= m) {
        for (int i = 0; i < n; i++) {
            b[t[i]-'a']++;
        }
        for (int i = 0; i+n <= m; i++) {
            if (a==b) yes|=true;
            b[t[i]-'a']--;
            if(i+n<m)b[t[i+n]-'a']++;
        }
    }
    cout << (yes?"YES\n":"NO\n");
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int t; cin >> t;
    while(t--)solve();
    cout << endl;
}
