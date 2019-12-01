#include <bits/stdc++.h>

using namespace std;

const int N = 3e4+10; 
bool pre[N][10], suf[N][10];
bool pin[10][10][10];

// consider as middle
void solve() {
    int n; cin >> n;
    string s; cin >> s;
    for (int i = 0; i < n; i++) {
        memcpy(pre[i+1], pre[i], sizeof pre[i+1]);
        pre[i+1][s[i]-'0'] = 1;
    }
    for (int i = n-1; i >= 0; i--) {
        memcpy(suf[i], suf[i+1], sizeof suf[i]);
        suf[i][s[i]-'0'] = 1;
    }
    for (int i = 1; i < n-1; i++) {
        int m = s[i]-'0';
        for (int l = 0; l < 10; l++) {
            for (int r = 0; r < 10; r++) {
                if (pre[i][l] && suf[i+1][r]) {
                    pin[l][m][r] = 1;
                }
            }
        }
    }
    int res = 0;
    for (int l = 0; l < 10; l++) {
        for (int m = 0; m < 10; m++) {
            for (int r = 0; r < 10; r++) {
                if (pin[l][m][r]) res++;
            }
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
