#include <bits/stdc++.h>

using namespace std;

const int N = 1005; 
char s[N][N];
int d[N][N];

void solve() {
    memset(s, '#', sizeof s);
    memset(d, 0, sizeof d);
    int n, m;
    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        cin >> (s[i] + 1);
    }
    auto cal = [&](int ii, int jj){
        int i = ii - 1;
        while (0 < i && s[i][jj] == 'O') {
            d[i][jj]++;
            i--;
        }
        i = ii + 1;
        while (i <= n && s[i][jj] == 'O') {
            d[i][jj]++;
            i++;
        }
        int j = jj -1;
        while (0 < j && s[ii][j] == 'O') {
            d[ii][j]++;
            j--;
        }
        j = jj + 1;
        while (j <= m && s[ii][j] == 'O') {
            d[ii][j]++;
            j++;
        }
    };

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            if (s[i][j] == 'B') cal(i, j);
        }
    }

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            if (s[i][j] == 'B') {
                cout << 'B';
            } else {
                cout << d[i][j];
            }
        }
        cout << "\n";
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
