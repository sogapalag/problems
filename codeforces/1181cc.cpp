#include <bits/stdc++.h>

using namespace std;

const int N = 1111; 

char s[N][N];

int R[N][N];
int D[N][N];

void solve() {
    memset(s, '#', sizeof s);
    int n, m;
    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        cin >> (s[i] + 1);
    }
    for (int i = 1; i <= n; i++) {
        for (int j = m; j >= 1; j--) {
            if (s[i][j] == s[i][j+1])
                R[i][j] = R[i][j+1] + 1;
            else
                R[i][j] = 1;
        }
    }
    for (int j = 1; j <= m; j++) {
        for (int i = n; i >= 1; i--) {
            if (s[i][j] == s[i+1][j])
                D[i][j] = D[i+1][j] + 1;
            else
                D[i][j] = 1;
        }
    }

    int res = 0;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            int h = D[i][j];
            int ii = i + h;
            if (ii > n || D[ii][j] != h) continue;
            int iii = ii + h;
            if (iii > n || D[iii][j] < h) continue;
            int tmp = m;
            for (int k = i; k < i + 3*h; k++) {
                tmp = min(tmp, R[k][j]);
            }
            res += tmp;
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
