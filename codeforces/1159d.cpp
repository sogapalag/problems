#include <bits/stdc++.h>

using namespace std;


void solve() {
    int n, k;
    cin >> n >> k;
    int a = (n-k)/2;
    a++;
    for (int i = 1; i <= n; i++) {
        cout << (i%a == 0);
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
