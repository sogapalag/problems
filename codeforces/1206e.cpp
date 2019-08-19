#include <bits/stdc++.h>

using namespace std;

int a[56][56];

void solve() {
    int n; cin >> n;
    auto q = [](int x,int y,int u, int v){
        cout << "? " << x << " " << y << " " << u << " "<< v<<endl;
    };
    auto r = [](){
        int x; cin >> x;
        return x;
    };
    a[1][1] = 1; a[n][n] = 0;
    // diag
    for (int i = 2; i < n; i++) {
        q(i-1,i-1,i,i);
        a[i][i] = a[i-1][i-1] ^ r() ^ 1;
    }
    // i row, i col
    for (int i = 1; i < n; i++) {
        for (int j = i+2; j <= n; j+=2) {
            q(i,j-2,i,j);
            a[i][j] = a[i][j-2] ^ r() ^ 1;
            q(j-2,i,j,i);
            a[j][i] = a[j-2][i] ^ r() ^ 1;
        }
    }
    a[1][2] = 1; // 1/0 assume
    // diag
    for (int i = 1; i < n; i++) {
        if (i+2 > n) break;
        q(i,i+1,i+1,i+2);
        a[i+1][i+2] = a[i][i+1] ^ r() ^ 1;
    }
    // row / col
    for (int i = 1; i < n; i++) {
        for (int j = i+3; j <= n; j+=2) {
            q(i,j-2,i,j);
            a[i][j] = a[i][j-2] ^ r() ^ 1;
        }
        for (int j = i+2; j <= n; j+=2) {
            q(j-2,i+1,j,i+1);
            a[j][i+1] = a[j-2][i+1] ^ r() ^ 1;
        }
    }
    // 1st col
    q(2,1,3,2);
    a[2][1] = a[3][2] ^ r() ^ 1;
    for (int i = 4; i <= n; i+=2) {
        q(i-2,1,i,1);
        a[i][1] = a[i-2][1] ^ r() ^ 1;
    }
    auto p = [&](){
        cout << "!" << endl;
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= n; j++) {
                cout << a[i][j];
            }cout << endl;
        }
        exit(0);
    };
    // flip black
    auto fl = [&](bool is_fl){
        for (int i = 1; i <= n; i++) {
            for (int j = 1+(i&1); j <= n; j+=2) {
                a[i][j] ^= is_fl;
            }
        }
        p();
    };
    bool flip;
    // when length=4, sum=0, flip which, sum still 0, but with different r()
    // so we can measure whether flip
    auto test = [&](int x,int y,int u,int v){
        q(x,y,u,v);
        flip = a[x][y]^a[u][v]^r()^1;
        fl(flip);
    };
    int sum;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            if (i+1<=n && j+2<=n) {
                sum = a[i][j] ^ a[i][j+1] ^ a[i][j+2] ^ a[i+1][j+2];
                if (sum == 0) test(i,j,i+1,j+2);
                sum = a[i][j] ^ a[i][j+1] ^ a[i+1][j+1] ^ a[i+1][j+2];
                if (sum == 0) test(i,j,i+1,j+2);
                sum = a[i][j] ^ a[i+1][j] ^ a[i+1][j+1] ^ a[i+1][j+2];
                if (sum == 0) test(i,j,i+1,j+2);
            }
            if (i+2<=n && j+1<=n) {
                sum = a[i][j] ^ a[i][j+1] ^ a[i+1][j+1] ^ a[i+2][j+1];
                if (sum == 0) test(i,j,i+2,j+1);
                sum = a[i][j] ^ a[i+1][j] ^ a[i+1][j+1] ^ a[i+2][j+1];
                if (sum == 0) test(i,j,i+2,j+1);
                sum = a[i][j] ^ a[i+1][j] ^ a[i+2][j] ^ a[i+2][j+1];
                if (sum == 0) test(i,j,i+2,j+1);
            }
        }
    }
    assert(false);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
