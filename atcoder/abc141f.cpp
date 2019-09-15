#include <bits/stdc++.h>

using namespace std;

using ll = long long;

const int L = 60; 
ll basis[L];

void insert_vec(ll msk) {
    for (int i = L-1; i >= 0; i--) { // large prefered
        if (!(msk&(1ll<<i))) continue;
        if (!basis[i]) {
            basis[i] = msk; return;
        }
        msk ^= basis[i];
    }
}

// sum: odd basic.
// for even part, we wanna max subset ^sum y.  then by parity, other part =y. too
void solve() {
    int n; cin >> n;
    vector<long long> a(n);
    ll sum = 0;
    for (auto& x: a) {
        cin >> x;
        sum ^= x;
    }
    for (auto& x: a) {
        x -= (x&sum); // remove odd part
        insert_vec(x);
    }
    ll y = 0;
    for (int i = L-1; i >= 0; i--) { // large prefered
        if (!basis[i]) continue;
        if (y & (1ll<<i)) continue;
        y ^= basis[i];
    }
    ll res = (y<<1) + sum;
    cout << res;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
