#include <bits/stdc++.h>

using namespace std;


void solve() {
    int n; cin >> n;
    string a; cin >> a;
    string res(n, '2');
    int i = 1;
    while (i < n && a[i]>= a[i-1]) {
        i++;
    }
    if (i < n) {
        res[i] = '1';
        int j = 0;
        while (j<i && a[j]<=a[i]) {
            res[j++] = '1';
        }
        char mi2 = a[j];
        char x1 = a[i];
        char x2 = a[i-1];
        for (int j = i+1; j < n; j++) {
            if (a[j] >= x2) {
                x2 = a[j];
            } else if (a[j] >= x1) {
                if (a[j] > mi2) {
                    cout << '-'; return;
                }
                res[j] = '1';
                x1 = a[j];
            } else {
                cout << '-'; return;
            }
        }
    }
    cout << res;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int t; cin >> t;
    while(t--) {
        solve();
        cout << "\n";
    }
    cout << endl;
}
