#include <bits/stdc++.h>

using namespace std;

char s[66][66];

void solve() {
    int n,m;
    cin >> n >> m;
    for (int i = 0; i < n; i++) {
        cin >> s[i];
    }
    bool all_A = true, all_P = true;
    bool has_row = false, has_col = false;
    for (int i = 0; i < n; i++) {
        bool tmp = true;
        for (int j = 0; j < m; j++) {
            char x = s[i][j];
            all_A &= x=='A';
            all_P &= x=='P';
            tmp &= x=='A';
        }
        has_row |= tmp;
    }
    for (int j = 0; j < m; j++) {
        bool tmp = true;
        for (int i = 0; i < n; i++) {
            tmp &= s[i][j]=='A';
        }
        has_col |= tmp;
    }
    bool corner = (s[0][0]=='A' || s[0][m-1]=='A' || s[n-1][0]=='A' || s[n-1][m-1]=='A');
    bool side = false;
    for (int i = 0; i < n; i++) {
        side |= s[i][0]=='A';
        side |= s[i][m-1]=='A';
    }
    for (int j = 0; j < m; j++) {
        side |= s[0][j]=='A';
        side |= s[n-1][j]=='A';
    }
    
    bool line_side = false;
    {
        bool tmp = true;
        for (int i = 0; i < n; i++) {
            tmp &= s[i][0]=='A';
        }
        line_side |= tmp;
    }
    {
        bool tmp = true;
        for (int i = 0; i < n; i++) {
            tmp &= s[i][m-1]=='A';
        }
        line_side |= tmp;
    }
    {
        bool tmp = true;
        for (int j = 0; j < m; j++) {
            tmp &= s[0][j]=='A';
        }
        line_side |= tmp;
    }
    {
        bool tmp = true;
        for (int j = 0; j < m; j++) {
            tmp &= s[n-1][j]=='A';
        }
        line_side |= tmp;
    }

    if (all_P) {
        cout << "MORTAL\n"; return;
    }
    if (all_A) {
        cout << "0\n"; return;
    }
    if (line_side) {
        cout << "1\n"; return;
    }
    if (corner || has_row || has_col) {
        cout << "2\n"; return;
    }
    if (side) {
        cout << "3\n"; return;
    }
    cout << "4\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int t; cin >> t;
    while(t--)solve();
    cout << endl;
}
