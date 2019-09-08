#include <bits/stdc++.h>

using namespace std;


// for res[j], only the ones pairity matter.
// let (#0,#1) of a,b   (z,p) (u,v), z*v+u*p.
//    asides carry's ones, only when (%k), their sum>=k
void solve() {
    int n; cin >> n;
    vector<int> a(n),b(n);
    for (auto& x: a) {
        cin >> x;
    }
    for (auto& x: b) {
        cin >> x;
    }
    const int L = 30;
    int res = 0;
    for (int j = 0; j < L; j++) {
        int k = 1<<j;
        int z = 0;
        for (auto& x: a) {
            if (!(x&k))z++;
        }int p = n-z;
        int u = 0;
        for (auto& x: b) {
            if (!(x&k))u++;
        }int v = n-u;
        z&=1, p&=1;
        u&=1, v&=1;
        int ans = z*v + u*p;
        vector<int> c(n);
        for (int i = 0; i < n; i++) {
            c[i] = b[i]%k;
        }
        sort(c.begin(), c.end());
        int carry = 0;
        for (auto& x: a) {
            int y = k - (x%k);
            int i = lower_bound(c.begin(), c.end(), y) - c.begin();
            carry ^= ((n-i)&1);
        }
        ans&=1;
        ans^=carry;
        if (ans) res |= k;
    }
    cout << res;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
