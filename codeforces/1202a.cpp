#include <bits/stdc++.h>

using namespace std;


// make first can make 1 in s to 0
void solve() {
    string s, t;
    cin >> s >> t;
    reverse(s.begin(), s.end());
    reverse(t.begin(), t.end());
    int k = 0;
    for (char c: t) {
        if (c == '1') break;
        k++;
    }
    int i = k;
    for (; s[i] != '1'; i++) {
    }
    cout << (i-k) << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int t; cin >> t;
    while(t--)solve();
    cout << endl;
}
