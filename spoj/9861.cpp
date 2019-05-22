#include <bits/stdc++.h>

using namespace std;


void solve() {
    typedef unsigned int u32;
    int n; cin >> n;
    u32 m; cin >> m;
    vector<u32> a(n+1);
    a[0] = 0;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    u32 res=0, crt=0;
    int j = 1;
    for (int i = 1; i <= n; i++) {
        crt -= a[i-1];
        while (crt <= m) {
            res = max(res, crt);
            if (j <= n)
                crt += a[j++];
            else
                break;
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
