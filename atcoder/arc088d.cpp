#include <bits/stdc++.h>

using namespace std;


// ...01...., flip parity odd. thus T = min max(i,n-i)
// sufficient, since, if >T or <N-T,  op:(k) + (k+1), flip kth
void solve() {
    string s;
    cin >> s;
    int n = s.size();
    int res = n;
    for (int i = 1; i < n; i++) {
        if (s[i] != s[i-1]) {
            res = min(res, max(i, n-i));
        }
    }
    cout << res;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
