#include <bits/stdc++.h>

using namespace std;

#define rep(i) for(int i=0;i<2;i++)

void solve() {
    int n; cin >> n;
    vector<bool> a(n);
    {
        string s; cin >> s;
        for (int i = 0; i < n; i++) {
            a[i] = s[i]=='x';
        }
    }
    vector<bool> res(n);
    rep(_x)rep(_y){
        res[0] = _x; res[1] = _y;
        for (int i = 2; i < n; i++) {
            res[i] = res[i-1]^a[i-1]^res[i-2];
        }
        if ((res[0]^res[1]^res[n-1]) == a[0] && a[n-1] == (res[n-2]^res[n-1]^res[0])) {
            for (bool x: res) {
                cout << (x?'W':'S');
            }
            return;
        }
    }
    cout << -1;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
