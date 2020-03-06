#include <bits/stdc++.h>

using namespace std;
using ll=long long;

// unclear statement, if W use R, it can take all Ps Remained. O cannot take others, 
// so optim structure, editorial kind of overkill
//  if P WW..WW
//     R
//  then for WW..WW, they must be ROO.OORRR
// let's say string is (P*.. . ) (W*)..(P*)(W*)
// then optim is       (O*) (RO..RR)*, where each (RO..RR) same 'W' or 'P'
// what does it mean?
// let's focus first using R, wlog P, then next time facing W, it must use R too.
//   since it won't be worser. then next time facing P, must use R too.
// i.e. each time a fresh differ letter, use R. actually one can see that's first R's contribution.
//   since each time use R, #R->1, there always one remained.
void solve() {
    int n; ll c, d;
    cin >> n >> c >> d;
    vector<int> a(n + 1);
    string s(n+1 , '#');
    for (int i = 0; i < n; i++) {
        cin >> a[i] >> s[i];
    }
    cin >> a[n];
    int las = a[n];
    ll res = n * d;
    ll suff = 0;
    for (int i = n-1; i >= 0; i--) {
        if (i == 0 || s[i-1]!=s[i]) {
            suff += c * (las - a[i]);
            las = a[i];
        } else {
            suff += min(d, c * (las - a[i]));
        }
        res = min(res, i*d + suff);
    }
    cout << res;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}
