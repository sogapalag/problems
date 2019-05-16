#include <bits/stdc++.h>

using namespace std;


void solve() {
    int T; cin >> T;
    while (T--) {
        int n; cin >> n;
        string s; cin >> s;
        bool flag = false;
        for (int i = n-11; i >= 0; i--) {
            if (s[i] == '8') {
                flag = true; break;
            }
        }
        if (flag){
            cout << "YES\n";
        }else{
            cout << "NO\n";
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
