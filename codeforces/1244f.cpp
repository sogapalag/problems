#include <bits/stdc++.h>

using namespace std;


//   xxxx (..........) yyyyy
// ->xxxx xx( yxyx )yy yyyyy
void solve() {
    int n, k;
    cin >> n >> k;
    string s; cin >> s;
    int i = 0;
    for (;i<n;i++) {
        if (s[i] != s[(i-1+n)%n])break;
    }
    if (i == n) { // all equal
        cout << s; return;
    }

    // len > 1  x..x
    vector<pair<int, int>> con;
    int len = 1;
    for (int j = 0; j < n; j++) {
        int x = (i+j)%n, y = (i+j+1)%n;
        if (s[x] != s[y]) {
            if (len > 1) {
                int z = (x-len+1+n)%n;
                con.emplace_back(z,x);
            }
            len = 1;
        } else len++;
    }

    auto flip = [](char c){
        return c=='W'?'B':'W';
    };

    // 01010101
    if (con.empty()) {
        assert(n%2 == 0);
        if (k&1) {
            for (auto& c: s) {
                c = flip(c);
            }
        }
        cout << s; return;
    }

    int m = con.size();
    for (int j = 0; j < m; j++) {
        int l = con[(j-1+m)%m].second;
        int r = con[j].first;
        int x = k;
        while ((r-l+n)%n > 1 && x > 0) {
            s[(l+1)%n] = s[l%n]; l++;
            s[(r-1+n)%n] = s[(r+n)%n]; r--;
            x--;
        }
        while ((r-l+n)%n > 1) {
            s[(l+1)%n] = flip(s[l%n]); l++;
            s[(r-1+n)%n] = flip(s[(r+n)%n]); r--;
        }
    }
    cout << s;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
