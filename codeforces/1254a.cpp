#include <bits/stdc++.h>

using namespace std;

char c[62];
int cnt[62];

// zig-zag
void solve() {
    int n,m,k;
    cin >> n >> m >> k;
    int rice = 0;
    vector<string> s(n);
    for (int i = 0; i < n; i++) {
        cin >> s[i];
        if (i&1) reverse(s[i].begin(), s[i].end());
        for (char x: s[i]) if (x == 'R') rice++;
    }
    int avg = rice/k, rem = rice%k;
    for (int i = 0; i < k; i++) {
        cnt[i] = avg + (i<rem);
    }

    int x = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (s[i][j] == 'R') {
                cnt[x]--;
            }
            s[i][j] = c[x];
            if (cnt[x] == 0 && x+1 < k) x++;
        }
        if (i&1) reverse(s[i].begin(), s[i].end());
        cout << s[i] << '\n';
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    for (int i = 0; i < 26; i++) {
        c[i] = 'a'+i;
        c[i+26] = 'A'+i;
    }
    for (int i = 0; i < 10; i++) {
        c[i+52] = '0'+i;
    }
    int t; cin >> t;
    while(t--)solve();
    cout << endl;
}
