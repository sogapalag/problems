#include <bits/stdc++.h>

using namespace std;


void solve() {
    int n; cin >> n;
    vector<string> s(n);
    vector<bool> trk(10, false);
    for (int i = 0; i < n; i++) {
        cin >> s[i];
        int x = s[i][0] - '0';
        trk[x] = true;
    }
    int cnt = 0;
    for (int i = 0; i < n; i++) {
        for (int j = i+1; j < n; j++) {
            if (s[i] == s[j]) {
                cnt++;
                for (int k = 0; k < 10; k++) {
                    if (!trk[k]) {
                        s[i][0] = '0' + k;
                        trk[k] = true;
                        break;
                    }
                }
                break;
            }
        }
    }
    cout << cnt << "\n";
    for (int i = 0; i < n; i++) {
        cout << s[i] << "\n";
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int t; cin >> t;
    while(t--)solve();
    cout << endl;
}
