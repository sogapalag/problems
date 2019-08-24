#include <bits/stdc++.h>

using namespace std;


// n, 2^k
void solve() {
    int n; cin >> n;
    for (int i = 0; i < n; i++) {
        for (int j = i+1; j < n; j++) {
            int k = 0;
            for (; k < 15; k++) {
                if ((i&(1<<k)) ^ (j&(1<<k))) break;                
            }
            cout << k+1 << ' ';
        }cout << "\n";
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
