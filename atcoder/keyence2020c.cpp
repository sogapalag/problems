#include <bits/stdc++.h>

using namespace std;


void solve() {
    int n,k,s;
    cin >> n >> k >> s;
    int x = s;
    int y = s == 1000*1000*1000 ? s-1 : s+1;
    for (int i = 0; i < k; i++) {
        cout << x << ' ';
    }
    for (int i = k; i < n; i++) {
        cout << y << ' ';
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}
