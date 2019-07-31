#include <bits/stdc++.h>

using namespace std;


void solve() {
    int b, w;
    cin >> b >> w;
    const int Y = 42;
    int b_x = 5, w_x = 6;
    if (b < w) {
        swap(b, w);
        b_x = 6;
        w_x = 7;
    }
    if (b > 3*w+1) {
        cout << "NO\n"; return;
    }
    cout << "YES\n";
    for (int i = 0; i < w; i++) {

        cout << b_x+2*i << " " << Y << "\n";
        cout << w_x+2*i << " " << Y << "\n";
    }
    int rem = b - w;
    if (rem > 0) {
        cout << b_x + 2*w << " " << Y << "\n";
        rem--;
    }
    while (rem > 0) {
        int i = 0;
        while (rem > 0 && i < w) {
            cout << w_x+2*i << " " << Y+1 << "\n";
            i++;
            rem--;
        }
        i = 0;
        while (rem > 0 && i < w) {
            cout << w_x+2*i << " " << Y-1 << "\n";
            i++;
            rem--;
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int q; cin >> q;
    while(q--)solve();
    cout << endl;
}
