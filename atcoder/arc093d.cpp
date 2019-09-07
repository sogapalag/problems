#include <bits/stdc++.h>

using namespace std;

char u[55][111];
char d[55][111];

void solve() {
    int a,b;
    cin >> a >> b;
    memset(u, '#', sizeof u);
    memset(d, '.', sizeof d);
    auto nex = [](int& i, int& j){
        if (j < 99) j += 2;
        else {i+=2; j = 1;}
    };
    int i = 1, j = 1;
    a--;
    while (a--) {
        u[i][j] = '.';
        nex(i,j);
    }
    b--;
    i = 2, j = 1;
    while (b--) {
        d[i][j] = '#';
        nex(i,j);
    }
    cout << "100 100\n";
    for (int i = 1; i <= 50; i++) {
        for (int j = 1; j <= 100; j++) {
            cout << u[i][j];
        }cout<<"\n";
    }
    for (int i = 1; i <= 50; i++) {
        for (int j = 1; j <= 100; j++) {
            cout << d[i][j];
        }cout<<"\n";
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
