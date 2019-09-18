#include <bits/stdc++.h>

using namespace std;


// if Ann could take left min, win for sure
void solve() {
    string s; cin >> s;
    char mi = 'z';
    for (char c: s) {
        if (c > mi) {
            cout << "Ann\n";
        } else {
            cout << "Mike\n";
            mi = min(mi, c);;
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
