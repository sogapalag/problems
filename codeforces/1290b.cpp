#include <bits/stdc++.h>

using namespace std;
using Freq=array<int,26>;

// l->r, i.e. a k-dim square, s[l..r] repre a path.
// \E another path doesn't meet original?
// thus k>=3, the path wouln't cut.
// k=2, draw a square, apparently if s[l]=s[r], all path must meet original in the middle.
void solve() {
    string s; cin >> s;
    int n = s.size();
    vector<Freq> sum(n+1);
    for (int i = 0; i < n; i++) {
        sum[i+1] = sum[i];
        sum[i+1][s[i]-'a']++;
    }
    int q; cin >> q;
    while (q--) {
        int l, r;
        cin >> l >> r;
        l--;
        if (r-l == 1) {
            cout << "Yes\n";
            continue;
        }
        Freq a = {};
        int has = 0;
        for (int i = 0; i < 26; i++) {
            a[i] = sum[r][i] - sum[l][i];
            if (a[i]>0) has++;
        }
        if (has >= 3) {
            cout << "Yes\n";
        } else {
            cout << (s[l]==s[r-1]?"No\n":"Yes\n");
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}
