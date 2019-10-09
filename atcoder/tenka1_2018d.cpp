#include <bits/stdc++.h>

using namespace std;

int d[450][450]; // >= 2*n

// must be complete graph K_k
void solve() {
    int n; cin >> n;
    int k = 1;
    auto c2 = [](int x){
        return x*(x-1)/2;
    };
    while (c2(k) < n) {
        k++;
    }
    if (c2(k) != n) {
        cout << "No"; return;
    }
    int edge_cnt = 1;
    for (int i = 0; i < k; i++) {
        for (int j = i+1; j < k; j++) {
            d[i][j] = d[j][i] = edge_cnt++;
        }
    }

    cout << "Yes\n";
    cout << k << "\n";
    for (int i = 0; i < k; i++) {
        cout << (k-1) << ' ';
        for (int j = 0; j < k; j++) {
            if (i != j) {
                cout << d[i][j] << ' ';
            }
        }cout << "\n";
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
