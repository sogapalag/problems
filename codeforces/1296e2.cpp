#include <bits/stdc++.h>

using namespace std;

bool occur_before[26][26];
int mex(int x){
    for (int i = 0; i < 26; i++) {
        if (!occur_before[x][i]) return i;
    }
    assert(false);
}
// if you feel same char should hold same color, would k-color, NP
// don't overcomplicated, greedy mex, or dp
void solve() {
    int n; cin >> n;
    string s; cin >> s;
    vector<int> res(n);
    for (int i = 0; i < n; i++) {
        int c = s[i]-'a';
        res[i] = mex(c);
        for (int k = 0; k < c; k++) {
            occur_before[k][res[i]] = true;
        }
    }
    int C = *max_element(res.begin(), res.end()) + 1;
    cout << C << "\n";
    for (auto& x: res) {
        cout << x+1 << ' ';
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}
