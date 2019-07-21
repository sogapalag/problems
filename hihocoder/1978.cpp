#include <bits/stdc++.h>

using namespace std;


void solve() {
    string s; cin >> s;
    int n = s.size();
    string res; res.reserve(n);
    int i = 0;
    while (i < n) {
        if (s[i]=='0') {
            res.push_back('C');
            i++;
        }else{
            if (s[i+1] == '0') {
                if (s[i+2] == '0') {
                    res.push_back('D');
                }else{
                    res.push_back('A');
                }
                i += 3;
            }else{
                res.push_back('B');
                i += 2;
            }
        }
    }
    cout << res;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
