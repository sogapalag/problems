#include <bits/stdc++.h>

using namespace std;

using Freq = array<int,26>;

void mini(Freq& a, const Freq& b) {
    for (int i = 0; i < 26; i++) {
        a[i] = min(a[i], b[i]);
    }
}

void solve() {
    int n; cin >> n;
    Freq cnt;
    fill(cnt.begin(), cnt.end(), 1000);
    for (int _ = 0; _ < n; _++) {
        string s; cin >> s;
        Freq tmp = {};
        for (char c:s) tmp[c-'a']++;
        mini(cnt, tmp);
    }
    for (int i = 0; i < 26; i++) {
        char x = 'a'+i;
        for (int _ = 0; _ < cnt[i]; _++) {
            cout << x;
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
