#include <bits/stdc++.h>

using namespace std;


void solve() {
    int M, D;
    cin >> M >> D;
    int cnt = 0;
    for (int i = 1; i <= M; i++) {
        for (int j = 1; j <= D; j++) {
            if (j < 20) continue;
            if ((j%10)<2) continue;
            if ((j/10) * (j%10) != i) continue;
            cnt++;
        }
    }
    cout << cnt;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
