#include <bits/stdc++.h>

using namespace std;


void solve() {
    string s; cin >> s;
    string x = s.substr(0, 2);
    string y = s.substr(2, 2);
    bool u = "01" <= x && x <= "12";
    bool v = "01" <= y && y <= "12";
    if (u && v) {
        cout << "AMBIGUOUS";
    }else if (u) {
        cout << "MMYY";
    }else if (v) {
        cout << "YYMM";
    }else {
        cout << "NA";
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
