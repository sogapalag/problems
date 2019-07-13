#include <bits/stdc++.h>

using namespace std;


void solve() {
    int x; cin >> x;
    x %= 4;
    if (x == 0) {
        cout << "1 A";
    } else if (x == 1) {
        cout << "0 A";
    } else if (x == 2){
        cout << "1 B";
    } else {
        cout << "2 A";
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
