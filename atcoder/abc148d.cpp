#include <bits/stdc++.h>

using namespace std;


void solve() {
    int n; cin >> n;
    int crt = 0;
    for (int _ = 0; _ < n; _++) {
        int x; cin >> x;
        if(x==crt+1) crt++;
    }
    int res = crt?n-crt:-1;
    cout << res;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
