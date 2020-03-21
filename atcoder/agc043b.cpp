#include <bits/stdc++.h>

using namespace std;

// ensure has mid
int f(vector<int>& a) {
    int n = a.size();
    vector<int> coeff(n);
    for (int i = 0; i < n; i++) {
        coeff[i] = (i&(n-1-i)) ? 0 : 1; // c(n-1,i) parity
    }
    int sum = 0;
    for (int i = 0; i < n; i++) {
        sum ^= ((a[i]&1) * coeff[i]);
    }
    return sum;
}

// write some test, would notice pattern.
// final almost 0/1, then realize 2 can only be produced by [0,2]*
void solve() {
    int n; cin >> n;
    bool notwo = true;
    vector<int> a(n);
    string s; cin >> s;
    for (int i = 0; i < n; i++) {
        a[i] = s[i]-'0';
        if (a[i]==2) notwo = false;
    }

    if (notwo) {
        vector<int> b(n-1);
        // let {0,2} -> {0,1}. then can decide by parity
        for (int i = 1; i < n; i++) {
            b[i-1] = abs(a[i]-a[i-1]);
            b[i-1] /= 2;
        }
        cout << f(b)*2;
    } else {
        cout << f(a);
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}
