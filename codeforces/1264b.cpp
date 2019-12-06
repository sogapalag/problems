#include <bits/stdc++.h>

using namespace std;


void solve() {
    int a[4];
    for (int i = 0; i < 4; i++) {
        cin >> a[i];
    }
    auto gg = [](){
        cout << "NO\n"; exit(0);
    };
    auto wp = [](){
        cout << "YES\n";
    };
    if (a[0] - a[1] >= 2 || a[3] - a[2] >= 2) {
        gg();
    }
    if (a[0] - a[1] == 1) {
        if (a[2] > 0 || a[3] > 0) {
            gg();
        }
        wp();
        cout << "0 ";
        for (int _ = 0; _ < a[1]; _++) {
            cout << "1 0 ";
        }return;
    }
    if (a[3] - a[2] == 1) {
        if (a[0] > 0 || a[1] > 0) {
            gg();
        }
        wp();
        cout << "3 ";
        for (int _ = 0; _ < a[2]; _++) {
            cout << "2 3 ";
        }return;
    }
    // valid always can trans to (01)* (21)* (23)*

    int x = a[1]-a[0];
    int y = a[2]-a[3];

    if (abs(x-y) > 1) gg();
    wp();
    if (x>y) cout << "1 ";
    for (int _ = 0; _ < a[0]; _++) {
        cout << "0 1 ";
    }
    int d = min(x,y);
    for (int _ = 0; _ < d; _++) {
        cout << "2 1 ";
    }
    for (int _ = 0; _ < a[3]; _++) {
        cout << "2 3 ";
    }
    if (y>x) cout << "2";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
