#include <bits/stdc++.h>

using namespace std;

// in theoretical term, Z/M may called mobius transform/inversion on subset lattice
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
// F=r(f). F[X] := f[W\X]
template <typename T>
inline void map_complement(vector<T>& f) {
    reverse(f.begin(), f.end());
}
// F=M'(f). F[X] := sum_{X sub S} (-1)^|S\X| f[S]
// M'Z' = Z'M' = I.
// M' = rMr.  M = rM'r
template <typename T>
inline void fast_superset_mobius_transform(vector<T>& f) {
    __loop(f) f[msk ^ 1<<i] -= f[msk];
}

// first it's easy to answer query [0,?]* and [1,?]*, by prep superset sum0, sum1
// the key deal [0,1,?]*: brute-force with conditional mobius. 2^{n/3}
// if ? is least, simply brute-force all sub
// wlog if 0 is least, note what we want is
// (a1 = some bits are 1 | a0 = some bits are 0) = (a1 | cap(b1^c)) = a1 | cup (-1)^ b1 = cup (-1)^ (ab)
void solve() {
    int n, q;
    cin >> n >> q;
    const int MSK = 1<<n; 
    string a; cin >> a;
    for (auto& x: a) {
        x -= '0';
    }
    vector<int> sum0(MSK), sum1(MSK);
    for (int m = 0; m < MSK; m++) {
        sum0[m^(MSK-1)] = a[m];
        sum1[m] = a[m];
    }
    fast_superset_zeta_transform(sum0);
    fast_superset_zeta_transform(sum1);
    while (q--) {
        string t; cin >> t;
        reverse(t.begin(), t.end());
        int m0 = 0, m1 = 0, m2 = 0;
        int c0 = 0, c1 = 0, c2 = 0;
        for (int i = 0; i < n; i++) {
            if (t[i] == '0') m0 |= 1<<i, ++c0;
            if (t[i] == '1') m1 |= 1<<i, ++c1;
            if (t[i] == '?') m2 |= 1<<i, ++c2;
        }
        int mi = min({c0,c1,c2});
        int res = 0;
        if (mi == c0) {
            for (int s0 = m0; s0 >= 0; (s0-=1)&=m0) {
                res += ((__builtin_popcount(s0)&1)? -1 : 1) * sum1[s0 | m1];
                if (s0 == 0) break;
            }
        } else if (mi == c1) {
            for (int s1 = m1; s1 >= 0; (s1-=1)&=m1) {
                res += ((__builtin_popcount(s1)&1)? -1 : 1) * sum0[s1 | m0];
                if (s1 == 0) break;
            }
        } else {
            for (int s2 = m2; s2 >= 0; (s2-=1)&=m2) {
                res += a[m1 | s2];
                if (s2 == 0) break;
            }
        }
        cout << res << "\n";
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}
