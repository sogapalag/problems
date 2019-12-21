#include <bits/stdc++.h>

using namespace std;


void solve() {
    int n, k;
    cin >> n >> k;
    string s; cin >> s;
    string t = s;
    for (int i = 0; i < n; i++) {
        t[i] = s[i%k];
    }
    for (int i = 0; i < n; i++) {
        if (t[i]<s[i]) goto nxt;
        if (t[i]>s[i]) break;
    }
    cout << n << "\n";
    cout << t; return;
nxt:;
    bool all9 = true;
    for (int i = 0; i < k; i++) {
        all9 &= s[i]=='9';
    }
    if (all9) {//no used
        n++;
        for (int i = 0; i < n; i++) {
            if (i%k==0)cout << '1';
            else cout << '0';
        }
    } else {
        int carry = 1;
        for (int i = k-1; i >= 0; i--) {
            int x = s[i]-'0';
            x += carry;
            s[i] = '0' +(x%10);
            carry = x/10;
        }
        for (int i = 0; i < n; i++) {
            t[i] = s[i%k];
        }
        cout << n << "\n";
        cout << t; return;
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
