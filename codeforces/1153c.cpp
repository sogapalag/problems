#include <bits/stdc++.h>

using namespace std;

void gg() {
    cout << ":(" << "\n";
    exit(0);
}
// pref-notin P, only it in P iff s[1..n-2] is valid '()' string, also s[0]s[n-1] can be '()'
// when check '?()' whether valid, note we need to put exact number missing '(' and ')'. then greedily put '('s first then ')'s, in'?' always valid if there is a valid solution.
void solve() {
    int n; cin >> n;
    string s; cin >> s;
    if (n & 1) gg();
    if (s[0] == ')' || s[n-1] == '(') gg();
    s[0] = '('; s[n-1] = ')';
    int a = 0, b = 0;
    int t = n-2;
    for (int i = 1; i <= t; i++) {
        if (s[i] == '(')
            a++;
        if (s[i] == ')')
            b++;
    }
    int c = t/2;
    for (int i = 1; i <= t; i++) {
        if (s[i] == '?') {
            if (a < c) {
                s[i] = '(';
                a++;
            } else {
                s[i] = ')';
                b++;
            }
        }
    }
    int stk = 0;
    for (int i = 1; i <= t; i++) {
        if (s[i] == '(')
            stk++;
        else
            stk--;
        if (stk < 0) gg();
        if (i == t && stk != 0) gg();
    }
    cout << s;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
