#include <bits/stdc++.h>

using namespace std;


// [0..n] +1 while can, split-by-0
// = increaing
void solve() {
    int n; cin >> n;
    int las = 0;
    int res = 0;
    for (int _ = 0; _ < n; _++) {
        int x; cin >> x;
        if (x > las) res += x-las;
        las = x;
    }
    cout << res;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
