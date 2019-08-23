#include <bits/stdc++.h>

using namespace std;

void solve() {
    cout << "? ";
    for (int i = 1; i <= 100; i++) {
        cout << i << ' ';
    }cout << endl;
    int y; cin >> y;
    y &= (1<<14)-1 - ((1<<7)-1);

    int k = 1<<7;
    cout <<"? ";
    for (int i = 1; i <= 100; i++) {
        cout << (i*k) << ' ';
    }cout << endl;
    int z; cin >> z;
    z &= (1<<7)-1;

    int res = y^z;
    cout << "! " << res << endl;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
