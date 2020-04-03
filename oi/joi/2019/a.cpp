#include <bits/stdc++.h>

using namespace std;

const int N = 3111; 
char s[N][N];
int c[N][N];
void solve() {
    int n, m;
    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        cin >> &s[i][1];
    }
    for (int j = 1; j <= m; j++) {
        for (int i = n; i >= 1; i--) {
            c[i][j] = c[i+1][j] + (s[i][j] == 'I');
        }
    }
    long long res = 0;
    for (int i = 1; i <= n; i++) {
        int r = 0;
        for (int j = m; j >= 1; j--) {
            r += (s[i][j] == 'O');
            if (s[i][j] == 'J') res += r * c[i][j];
        }
    }
    cout << res << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}
