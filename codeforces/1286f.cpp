#include <bits/stdc++.h>

using namespace std;
using ll=long long;
// O(n 2^n) Yates
#define __loop(f) \
    for (int i = 0, n = 31-__builtin_clz((int)f.size()), MSK = 1<<n; i < n; i++)\
        for (int msk = 0; msk < MSK; msk++)\
            if (msk>>i&1)

// F=Z(f). F[X] := sum_{S sub X} f[S]
template <typename T>
inline void fast_subset_zeta_transform(vector<T>& f) {
    __loop(f) f[msk] += f[msk ^ 1<<i];
}
// F=M(f). F[X] := sum_{S sub X} (-1)^|X\S| f[S]. 
// MZ = ZM = I
template <typename T>
inline void fast_subset_mobius_transform(vector<T>& f) {
    __loop(f) f[msk] -= f[msk ^ 1<<i];
}
// F=Z'(f). F[X] := sum_{X sub S} f[S]
// Z' = rZr. Z = rZ'r
template <typename T>
inline void fast_superset_zeta_transform(vector<T>& f) {
    __loop(f) f[msk ^ 1<<i] += f[msk];
}

void solve() {
    int n; cin >> n;
    vector<ll> a;
    for (int _ = 0; _ < n; _++) {
        ll x; cin >> x;
        if (x != 0) a.push_back(x);
    }
    n = a.size();
    if (n == 0) {
        cout << 0; return;
    } else if (n == 1) {
        cout << 1; return;
    }
    const int MSK = 1<<n; 
    vector<ll> sum(MSK);
    for (int i = 0; i < n; i++) {
        sum[1<<i] = a[i];
    }
    fast_subset_zeta_transform(sum);
    vector<bool> good(MSK);
    int m = n/2;
    const int LO = 1<<m; 
    for (int hi = 0; hi < MSK; hi+=LO) {
        vector<ll> ds; // deltas: {A-B}
        // exclude 0,hi
        for (int sub = (hi-1)&hi; sub >= 1; (sub-=1)&=hi) {
            ds.push_back(sum[sub] - sum[sub^hi]);
        }
        sort(ds.begin(), ds.end());
        for (int lo = 0; lo < LO; lo++) {
            int nodes = __builtin_popcount(hi|lo);
            // N-1 edges, add N-1 parity
            if ((sum[hi|lo] + nodes-1) % 2 != 0) continue;
            bool yes = false;
            for (int sub = lo; sub >= 0; (sub-=1)&=lo) {
                ll d = sum[sub] - sum[sub^lo];
                //// hi sub could be 0
                //if (sub != 0 && abs(d - sum[hi]) <= nodes-1)
                //    yes |= true;
                //// hi sub could be full
                //if (sub != lo && abs(d + sum[hi]) <= nodes-1)
                //    yes |= true;
                // hi could be 0.
                if (sub > 0 && sub < lo+hi && abs(d - sum[hi]) <= nodes -1)
                    yes |= true;
                if (sub < lo && sub+hi > 0 && abs(d + sum[hi]) <= nodes - 1)
                    yes |= true;
                // |x+d| <= N-1
                auto lb = lower_bound(ds.begin(), ds.end(), -d - (nodes-1));
                auto ub = upper_bound(ds.begin(), ds.end(), -d + (nodes-1));
                if (lb != ub) yes |= true;
                if (yes) {
                    good[hi|lo] = true;
                    //cerr << hi << ' ' << lo << endl;
                    break;
                }
                if (sub == 0) break;
            }
        }
    }

    // split set to good sub, one good sub implies we can use N-1<N,
    vector<int> dp(MSK, 0);
    for (int msk = 1; msk < MSK; msk++) {
        for (int sub = msk; sub >= 1; (sub-=1)&=msk) {
            dp[msk] = max(dp[msk], good[sub] + dp[msk^sub]);
        }
    }
    cout << (n - dp[MSK-1]);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
