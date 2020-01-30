#include <bits/stdc++.h>

using namespace std;

// SNIPPETS_START transform_set_sim
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
// SNIPPETS_END
