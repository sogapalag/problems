#include <bits/stdc++.h>

using namespace std;
using ll=long long;

void solve() {
    int D; string s;
    cin >> D >> s;
    int lim = 0;
    for (char c:s)if(c=='S')lim++;
    if (D < lim) {
        cout << "IMPOSSIBLE\n"; return;
    }
    auto f = [&](){
        ll res = 0;
        ll x = 1;
        for (char c:s) {
            if (c=='C') x<<=1;
            else res += x;
        }
        return res;
    };
    int inv = 0;
    int n = s.size();
    // brute-force check
    while (f() > D) {
        // greedy
        for (int i = n-1; i >= 1; i--) {
            if (s[i]=='S' && s[i-1]=='C') {
                swap(s[i-1], s[i]); break;
            }
        }
        inv++;
    }
    cout << inv << '\n';
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int T; cin >> T;
    for (int t = 1; t <= T; t++) {
        cout << "Case #" << t << ": ";
        solve();
    }
    return 0;
}
