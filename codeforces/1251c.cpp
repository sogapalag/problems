#include <bits/stdc++.h>

using namespace std;


void solve() {
    string s; cin >> s;
    int n = s.size();
    string odd, even;
    for (char c: s) {
        if ((c-'0')&1) odd.push_back(c);
        else even.push_back(c);
    }
    n = odd.size(); int m = even.size();
    int i = 0, j = 0;
    string res; res.reserve(n+m);
    while (i < n && j < m) {
        if (odd[i] < even[j]) {
            res.push_back(odd[i++]);
        } else {
            res.push_back(even[j++]);
        }
    }
    while (i < n) {
        res.push_back(odd[i++]);
    }
    while (j < m) {
        res.push_back(even[j++]);
    }
    cout << res << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int t; cin >> t;
    while(t--)solve();
    cout << endl;
}
