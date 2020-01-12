#include <bits/stdc++.h>

using namespace std;


// simple reflection
void solve() {
    int n; cin >> n;
    string s; cin >> s;
    for (auto& x: s) {
        x = (x=='S'?'E':'S');
    }
    cout << s;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int T; cin >> T;
    for (int t = 1; t <= T; t++) {
        cout << "Case #" << t << ": ";
        solve();
        cout << "\n";
    }
    fflush(stdout);
}
