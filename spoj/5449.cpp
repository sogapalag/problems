#include <bits/stdc++.h>

using namespace std;


void solve() {
    int T = 1;
    while (true) {
        string s;
        cin >> s;
        if (s[0] == '-') return;
        int stk = 0;
        int res = 0;
        for (auto& c: s) {
            if (c == '{') {
                stk++;
            }else {
                if (stk) {
                    stk--;
                }else {
                    stk++;
                    res++;
                }
            }
        }
        res += stk/2;
        cout << T++ << ". " << res << "\n";
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
