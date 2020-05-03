#include <bits/stdc++.h>

using namespace std;


// only when (0,0) invalid
// try to avoid, just when (1,1,x) check next use which, decide (2,0) or (0,2)
// other case put more to less
void solve() {
    int n; cin >> n;
    vector<int> a(3);
    for (auto& x: a) cin >> x;
    vector<string> s(n);
    for (auto& x: s) cin >> x;
    string res(n,'?');
    for (int _ = 0; _ < n; _++) {
        int i = s[_][0]-'A';
        int j = s[_][1]-'A';
        if (a[i] == 0 && a[i]==a[j]) {
            cout << "No"; return;
        }
        int k = i;
        if (a[i] == 1 && a[i]==a[j]) {
            if (_+1<n) {
                int ii = s[_+1][0]-'A';
                int jj = s[_+1][1]-'A';
                if (i==ii||i==jj) k = i;
                else k = j;
            }
        } else {
            k = a[i]>a[j]? j : i;
        }
        res[_] = char('A'+k);
        ++a[k]; --a[k==i?j:i];
    }
    cout << "Yes\n";
    for (char c:res) cout << c << '\n';
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}
