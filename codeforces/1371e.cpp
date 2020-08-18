#include <bits/stdc++.h>

using namespace std;


// first note x+i >= a
// then when consider sorted a. how many pos can insert a forward.
//   => f(x):= prod (i - (a-x) + 1). // which is wrong. since might a-x<0
// another correct view is to think how many can put into pos i.
//  let b = #a<=x+i, f(x) = prod (b-i).
//   https://codeforces.com/blog/entry/79624?#comment-654831 detail
// key is note valid range is continous.
//
// let's use my first view.
//  1. i >= a-x forsure  deduce l
//  2. a_{p-1+i} cannot insert forward >=p, deduce r
void solve() {
    int n,p;
    cin >> n >> p;
    vector<int> a(n);
    for (auto& x: a) cin >> x;
    sort(a.begin(), a.end());
    int l = 0, r = 1e9+10;
    for (int i = 0; i < n; i++) {
        l = max(l, a[i]-i);
        if (i+p-1 < n) r = min(r, a[i+p-1]-i);
    }
    if (l >= r) cout << "0\n";
    else {
        cout << r-l << '\n';
        for (int x = l; x < r; x++) {
            cout << x << ' ';
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}
