#include <bits/stdc++.h>

using namespace std;

const int N = 128; 
char g[N][N];

void solve() {
    int n,m,a,b,c;
    cin >> n >> m >> a >> b >> c;
    if ((n*m)&1) {
        cout << "IMPOSSIBLE"; return;
    }
    bool traned = false;
    if (m&1) {
        traned = true;
        swap(n,m);
        swap(a,b);
    }
    memset(g, '?', sizeof g);
    b /= 2;
    for (int i = 1; i+1 <= n; i+=2) {
        for (int j = 1; j+1 <= m && (b>0||c>0); j+=2) {
            char x = 'a';
            while (x==g[i-1][j] || x==g[i][j-1] || x==g[i-1][j+1] || x==g[i+1][j-1]) {
                x++;
            }
            if (c>0) {
                g[i][j]=g[i][j+1]=g[i+1][j]=g[i+1][j+1]=x;
                c--;
            } else {
                g[i][j]=g[i+1][j] = x;
                x = 'a'; // ||
                while (x==g[i-1][j] || x==g[i][j] || x==g[i-1][j+1] || x==g[i+1][j-1]) {
                    x++;
                }
                g[i][j+1]=g[i+1][j+1] = x;
                b--;
            }
        }
    }
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j+1 <= m && (a>0); j+=2) if(g[i][j] == '?'){
            char x = 'a';
            while (x==g[i-1][j] || x==g[i][j-1] || x==g[i-1][j+1] || x==g[i+1][j-1]) {
                x++;
            }
            g[i][j] = g[i][j+1] = x;
            a--;
        }
    }
    if (traned) {
        int M = max(n,m);
        for (int i = 1; i <= M; i++) {
            for (int j = 1; j < i; j++) {
                swap(g[i][j], g[j][i]);
            }
        }
        swap(n,m);
    }
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            if (g[i][j] == '?') {
                cout << "IMPOSSIBLE"; return;
            }
        }
    }
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            cout << g[i][j];
        }cout << '\n';
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}
