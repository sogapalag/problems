#include <bits/stdc++.h>

using namespace std;


void solve() {
    string s; cin >> s;
    int n = s.size();
    vector<int> res;
    for (int i = 0; i < n-2; i++) {
        if (i+5 <= n && s.substr(i, 5) == "twone") {
            res.push_back(i+2); i += 4;
        } else if (s.substr(i,3) == "two") {
            res.push_back(i+1); i += 2;
        } else if (s.substr(i,3) == "one") {
            res.push_back(i+1); i += 2;
        }
    }
    cout << res.size() << "\n";
    for (auto& x: res) {
        cout << (x+1) << ' ';
    }cout << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int t; cin >> t;
    while(t--)solve();
    cout << endl;
}
