#include <bits/stdc++.h>

using namespace std;

const int N = 100005; 
int a[2][N];

void solve() {
    int n,q;
    cin >> n >> q;
    int cnt = 0;
    auto toggle = [&](int i, int j){
        int x = a[i][j] ? -1 : 1;
        for (int d = -1; d <= 1; d++) {
            cnt += x * (a[i^1][j+d]);
        }
        a[i][j] ^= 1;
    };
    while (q--) {
        int x,y;
        cin >> x >> y;
        x--;
        toggle(x,y);
        if (!a[0][1] && !a[1][n] && cnt == 0) {
            cout << "Yes\n";
        }else {
            cout << "No\n";
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}
