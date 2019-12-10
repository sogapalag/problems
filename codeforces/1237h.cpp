#include <bits/stdc++.h>

using namespace std;

// (----->k)(->2) after ops k, k+2
// (2<-)(----->k)
void solve() {
    string s, t; 
    cin >> s >> t;
    int n = s.size();
    int a[2][2] = {};
    int b[2][2] = {};
    for (int i = 0; i < n; i+=2) {
        a[s[i]-'0'][s[i+1]-'0']++;
        b[t[i]-'0'][t[i+1]-'0']++;
    }
    if (a[0][0] != b[0][0] || a[1][1] != b[1][1]) {
        cout << "-1\n\n"; return;
    }
    vector<int> res;
    int x = a[0][1] - a[1][0];
    int y = b[1][0] - b[0][1];
    int p = -1; // should reverse t prefix
    if (x != y) {
        int d = 0;
        for (int i = 0; i < n; i+=2) {
            if (s.substr(i, 2) == "01") d -= 2;
            if (s.substr(i, 2) == "10") d += 2;
            if (x + d == y) {
                res.push_back(i+2);
                reverse(s.begin(), s.begin() + i+2);
                goto handy;
            }
        }
        d = 0;
        for (int i = 0; i < n; i+=2) {
            if (t.substr(i, 2) == "01") d += 2;
            if (t.substr(i, 2) == "10") d -= 2;
            if (x == y + d) {
                p = i+2;
                reverse(t.begin(), t.begin() + p);
                goto handy;
            }
        }
    }
handy:
    for (int i = 0; i < n; i+=2) {
        int j = n-i-2; // find t backwards
        auto target = t.substr(j, 2);
        swap(target[0], target[1]);
        for (int k = i; k < n; k+=2) {
            if (s.substr(k, 2) == target) {
                if (k) {
                    res.push_back(k);
                    reverse(s.begin(), s.begin() + k);
                }
                res.push_back(k+2);
                reverse(s.begin(), s.begin() + k+2);
                break;
            }
        }
    }
    assert(s == t);
    if (p != -1) {
        res.push_back(p);
    }
    cout << res.size() << "\n";
    for (auto& x: res) {
        cout << x << ' ';
    }cout << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int t; cin >> t;
    while(t--)solve();
    cout << endl;
}
