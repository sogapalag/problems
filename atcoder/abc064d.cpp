#include <bits/stdc++.h>

using namespace std;


void solve() {
    int n; cin >> n;
    string s; cin >> s;
    int sum = 0, mi = 0;
    for (char c:s) {
        sum += c=='('?1:-1;
        mi = min(mi, sum);
    }
    if (mi < 0) sum -= mi;
    mi *= -1;
    string res;
    for (int i = 0; i < mi; i++) {
        res.push_back('(');
    }
    res += s;
    for (int i = 0; i < sum; i++) {
        res.push_back(')');
    }
    cout << res;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
