#include <bits/stdc++.h>

using namespace std;
using ll=long long;

ll n,k;
ll B,S;

// find I'th Block sum
ll find(ll I) {
    if (I == 0) return S;
    ll i = I/k, t = I%k;
    ll s = find(i);
    ll l = i*B + t*k + 1;
    ll r = l + k-1;
    ll res = (l+r) * (r-l+1) / 2;
    // shift
    if (s <= l) res += k;
    else if (s <= r) res += r-s+1;
    return res;
}

// claim:
//   1. each Block has exactly one sum, 
//   2. each Block' vals are exactly [i*B+1, (i+1)*B]
// note Block view is NOT the chonological seq. just indicate I-sum create by (i,t)th k
// https://codeforces.com/blog/entry/71216?#comment-557137
void solve() {
    cin >> n >> k;
    B = k*k+1;
    S = k*(k+1)/2;
    ll I = (n-1) / B;
    ll val = find(I);
    if (n == val) {
        cout << (I+1)*(k+1);
    } else {
        ll p = n - I - (val < n); // remove special in Block view
        cout << p + (p-1)/k; // + #create special in chono. view
    }
    cout << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int T; cin >> T;
    for (int t = 0; t < T; t++) {
        solve();
    }
    return 0;
}
