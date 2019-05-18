#include <bits/stdc++.h>

using namespace std;


void solve() {
    int n; cin >> n;
    char v[5] = {'a', 'e', 'i', 'o', 'u'};
    int i = 5;
    for (; i*i <= n; i++) {
        if (n % i == 0){
            int k = n/i;
            for (int j = 0; j < i; j++) {
                for (int u = 0; u < k; u++) {
                    cout << v[(j+u) % 5];
                }
            }
            return;
        }
    }
    cout << -1;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
