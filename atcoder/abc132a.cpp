#include <bits/stdc++.h>

using namespace std;


void solve() {
    vector<int> cnt(26, 0);
    for (int i = 0; i < 4; i++) {
        char c; cin >> c;
        cnt[c-'A']++;
    }
    int x = 0;
    for (int i = 0; i < 26; i++) {
        if (cnt[i] == 2) x++;
    }
    cout << ((x==2)?"Yes":"No");
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
