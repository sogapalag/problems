#include <bits/stdc++.h>

using namespace std;


void solve() {
    string s; cin >> s;//s has 4, so a,b>0
    string a,b;
    for (auto& c: s) {
        if (c=='4') {
            a.push_back('2');
            b.push_back('2');
        } else {
            a.push_back('0');
            b.push_back(c);
        }
    }
    auto clz = [](string& t){
        reverse(t.begin(), t.end());
        while (t.back() == '0') {
            t.pop_back();
        }
        reverse(t.begin(), t.end());
    };
    clz(a); clz(b);
    cout << a << ' ' << b;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int T; cin >> T;
    for (int t = 1; t <= T; t++) {
        cout << "Case #" << t << ": ";
        solve();
        cout << "\n";
    }
    fflush(stdout);
}
