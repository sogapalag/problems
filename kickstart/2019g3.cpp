#include <bits/stdc++.h>

using namespace std;
using ll=long long;
const int N = 1<<20; 
ll a[N], b[N];
ll c[N];

void solve() {
    int n, H;
    cin >> n >> H;
    vector<int> A(n), B(n);
    for (auto& x: A) {
        cin >> x;
    }
    for (auto& x: B) {
        cin >> x;
    }
    const int MSK = 1<<n; 
    for (int msk = 0; msk < MSK; msk++) {
        ll sum = 0;
        for (int i = 0; i < n; i++) {
            if (msk & (1<<i)) sum += A[i];
        }
        a[msk] = sum >= H;
        
        sum = 0;
        for (int i = 0; i < n; i++) {
            if (msk & (1<<i)) sum += B[i];
        }
        b[msk] = sum >= H;
    }

    // we wanna transform idcator a[] to subset sum a'[]: i.e. a'[msk] = sum a[sub], sub of msk
    // the key technique is process by bit-oder in out-loop. then we don't have dup like inner-loop
    // since we can focus on each sub, there is only one path to contribute to msk.
    for (int i = 0; i < n; i++) {
        for (int msk = 0; msk < MSK; msk++) {
            if (msk & (1<<i)) {
                a[msk] += a[msk^(1<<i)];
                b[msk] += b[msk^(1<<i)];
            }
        }
    }

    ll res = 0;
    int u = n&1;
    // one method, IEP
    for (int msk = 0; msk < MSK; msk++) {
        c[msk] = a[msk] * b[msk];
        int v = __builtin_popcount(msk) & 1;
        (u^v)? res -= c[msk] : res += c[msk];
    }
    // second method, like prefix(sub)-sum above, we can view each sub contribute, -c to one bit more msk.
    for (int i = 0; i < n; i++) {
        for (int msk = 0; msk < MSK; msk++) {
            if (msk & (1<<i)) c[msk] -= c[msk^(1<<i)];
        }
    }
    assert(res == c[MSK-1]);
    cout << res;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int T; cin >> T;
    for (int t = 1; t <= T; t++) {
        cout << "Case #" << t << ": ";
        solve();
        cout << "\n";
    }
    fflush(stdout);
}
