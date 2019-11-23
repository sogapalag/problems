#include <bits/stdc++.h>

using namespace std;

const int N = 333; 
char s[N][N];
int a[N][N];

void solve() {
    int n,m,k;
    cin >> n >> m >> k;
    for (int i = 1; i <= n; i++) {
        cin >> (s[i]+1);
    }

    int u = 1, l = 1;
    int x = 1;
    for (int i = 1; i <= n; i++) {
        l = 1;
        bool find = false;
        for (int j = 1; j <= m; j++) {
            if (s[i][j]!='#')continue;
            find = true;
            for (int _i = u; _i <= i; _i++) {
                for (int _j = l; _j <= j; _j++) {
                    a[_i][_j] = x;
                }
            }
            x++;
            l = j+1;
        }
        if (find) u = i+1;
    }
    for (int i = 1; i <= n; i++) {
        if (!a[i][1]) { // last rows could empty
            for (int j = 1; j <= m; j++) {
                a[i][j] = a[i-1][j];
            }
        }
        for (int j = 1; j <= m; j++) {
            if (!a[i][j]) a[i][j] = a[i][j-1]; // some rows col-end could be empty
            cout << a[i][j] << ' ';
        }cout << "\n";
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
