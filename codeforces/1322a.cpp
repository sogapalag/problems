#include <bits/stdc++.h>

using namespace std;


// greedy use -1....0
void solve() {
    int n; cin >> n;
    string s; cin >> s;
    if (n&1) {
        cout << -1; return;
    }
    vector<int> a(n + 1);
    for (int i = 0; i < n; i++) {
        int x = s[i] == '(' ? 1 : -1;
        a[i + 1] = a[i] + x;
    }
    if (a[n] != 0) {
        cout << -1; return;
    }
    int i = 1;
    int res = 0;
    while (i <= n) {
        while (i <= n && a[i] >= 0) {
            i++;
        }
        if (i > n) break;
        int j = i+1;
        while (a[j] < 0) {
            j++;
        }
        assert(a[j] == 0);
        res += j - i + 1;
        i = j + 1;
    }
    cout << res;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}
