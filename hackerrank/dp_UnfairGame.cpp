#include <bits/stdc++.h>

using namespace std;

#define hbit(x) 1ll<<(63-__builtin_clzll(x))
using ll=long long;
int n;


ll f(ll sum, vector<ll> a) {
    ll cost = 0;
    while (sum) {
        ll k = hbit(sum); // int might -..
        ll mx_tail = -1; int id = -1;
        for (int i = 0; i < n; i++) {
            if (!(a[i] & k) && mx_tail < (a[i]%k)) {
                mx_tail = a[i] % k;
                id = i;
            }
        }
        //printf("%x\n", sum);
        //printf("%x %x %x\n", a[0], a[1], a[2]);
        if (id == -1) {
            ll tmp = 1ll << 40;
            for (int i = 0; i < n; i++) {
                vector<ll> b = a; // better create new one
                ll fil = k - b[i]%k;
                b[i] += fil;
                tmp = min(tmp, fil + f(sum ^ a[i] ^ b[i], b));
            }
            return tmp;
        } else {
            ll fil = k - mx_tail;
            cost += fil;
            sum ^= a[id] ^ (a[id]+=fil);
        }
    }
    return cost;
}

// u32 is sufficient to store cost, but large need ll.
// careful vector pass.
// 1
// 3
// 13 23 27
// // 27
void solve() {
    cin >> n;
    vector<ll> a(n);
    ll sum = 0;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        sum ^= a[i];
    }
    cout << f(sum, a) << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int t; cin >> t;
    while (t--) solve();
    cout << endl;
}
