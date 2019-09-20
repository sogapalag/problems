#include <bits/stdc++.h>

using namespace std;

const int N = 311; 
int a[N][N];

void solve() {
    int n; cin >> n;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> a[i][j];
        }
    }
    long long res = 0;
    for (int i = 0; i < n; i++) {
        for (int j = i+1; j < n; j++) {
            int direct = a[i][j];
            bool important = true;
            for (int k = 0; k < n; k++) {
                if (k==i||k==j) continue;
                int other = a[i][k] + a[k][j];
                if (other < direct) {
                    cout << -1; return;
                }else if (other == direct) {
                    important = false;
                }
            }
            if (important) res += direct;
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
