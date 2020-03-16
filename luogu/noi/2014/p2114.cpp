#include <bits/stdc++.h>

using namespace std;


// bit independent
void solve() {
    int n,m;
    cin >> n >> m;
    vector<pair<char,int>> gates(n);
    for (int i = 0; i < n; i++) {
        string s; int t;
        cin >> s >> t;
        if (s[0]=='A') gates[i] = {'&', t};
        else if (s[0]=='O') gates[i] = {'|', t};
        else gates[i] = {'^', t};
    }
    const int MSK = 1<<30; 
    int out[2] = {0, MSK-1};
    for (int& x:out) {
        for (auto& _: gates) {
            char op; int t;
            tie(op, t) = _;
            if (op=='&') x&=t;
            else if (op=='|') x|=t;
            else x^=t;
        }
    }
    int x = 0, y = 0;
    for (int i = 29; i >= 0; i--) {
        int r0 = out[0]>>i&1;
        int r1 = out[1]>>i&1;
        if (r0 == 0 && r1 == 1 && (x + (1<<i)) <= m) {
            x += 1<<i;
            y += 1<<i;
        } else {
            y += r0<<i;
        }
    }
    cout << y;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}
