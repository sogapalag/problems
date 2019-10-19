#include <bits/stdc++.h>

using namespace std;

const int N = 2048; 
using V=bitset<N>;
V a[N], L[N], R[N];
// a[i] win[..]
// L[l][i]: [l..i) can be left sub tree of i
// R[r][i]: (i..r] can be right sub tree of i

// champion iff make a rooted binary tree.
// update by width order,
// e.g. for we wanna know if L[l][r] set, i.e.
// if \E k in [l..r) can be root of [l..r) aka, L[l] & R[r-1]
//  and r should win k, i.e. &a[r]
void solve() {
    int n; cin >> n;
    for (int i = 1; i < n; i++) {
        string s; cin >> s;
        for (int j = 0; j < i; j++) {
            int x = s[j]-'0';
            a[i][j] = x;
            a[j][i] = x^1;
        }
    }
    for (int i = 0; i < n; i++) {
        L[i][i] = R[i][i] = 1;
    }
    for (int d = 1; d < n; d++) {
        for (int l = 0, r; (r=l+d) < n; l++) {
            if ((L[l] & R[r-1] & a[r]).count()) L[l][r] = 1;
            if ((L[l+1] & R[r] & a[l]).count()) R[r][l] = 1;
        }
    }
    int res = (L[0] & R[n-1]).count();
    cout << res;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
