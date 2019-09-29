#include <bits/stdc++.h>

using namespace std;


void solve() {
    int l, r;
    cin >> l >> r;
    for (int i = l; i <= r; i++) {
        auto s = to_string(i);
        set<char> st;
        for (char c:s) st.insert(c);
        if (st.size() == s.size()) {
            cout << i; return;
        }
    }
    cout << -1;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
