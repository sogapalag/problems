#include <bits/stdc++.h>

using namespace std;


void solve() {
    int n; cin >> n;
    string s; cin >> s;
    int l=0,r=0;
    for (char x:s) {
        if (x=='L')l++;
        else r++;
    }
    // guess what, it's n+1
    int res = r + l + 1;
    cout << res;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
