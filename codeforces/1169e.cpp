#include <bits/stdc++.h>

using namespace std;

const int N = 3e5+5; 
const int L = 19; 

int a[N];
int go[N][L];
int las[L];

// record cloest las[j], always a[x] ->(by-j) las[j] ->(dp relation) [k]
void solve() {
    int n, q;
    cin >> n >> q;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    for (int i = 0; i <= n; i++) {
        for (int j = 0; j < L; j++) {
            go[i][j] = n;
        }
    }
    for (int j = 0; j < L; j++) {
        las[j] = n;
    }
    for (int i = n-1; i >= 0; i--) {
        for (int j = 0; j < L; j++) {
            if (a[i] & (1<<j)) {
                for (int k = 0; k < L; k++) {
                    go[i][k] = min(go[i][k], go[las[j]][k]);
                }
                las[j] = i;
                go[i][j] = i;
            }
        }
    }
    while (q--) {
        int x, y;
        cin >> x >> y;
        x--, y--;
        bool ok = false;
        for (int j = 0; j < L; j++) {
            ok |= (a[y] & (1<<j)) && go[x][j] <= y;
        }
        cout << (ok? "Shi": "Fou") << "\n";
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
