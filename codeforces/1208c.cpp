#include <bits/stdc++.h>

using namespace std;

int res[1111][1111];
#define rep(i) for(int i=0;i<2;i++)

void solve() {
    int n; cin >> n;
    for (int i = 0; i < n/2; i++) {
        for (int j = 0; j < n/2; j++) {
            rep(x)rep(y){
                res[2*i+x][2*j+y] = ((n/2 * i + j)*4)|(x*2)|y;
            }
        }
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cout << res[i][j] << ' ';
        }cout<<"\n";
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
