#include <bits/stdc++.h>

using namespace std;


// another way is using two stack size cnt. each time compare.
// but below method also work, greedily to match last x, aka mini stack size.
void solve() {
    int n; cin >> n;
    string s; cin >> s;
    int x = 0, y = 0;
    for (auto& c: s) {
        if (c == '(') {
            cout << x; x ^= 1;
        }else {
            cout << y; y ^= 1;
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
