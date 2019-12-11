#include <bits/stdc++.h>

using namespace std;
// https://arxiv.org/pdf/cs/0611101.pdf

// not significant fast
//static const int bit[28] = {
//    0x1,      0x2,      0x4,      0x8,
//    0x10,     0x20,     0x40,     0x80,
//    0x100,    0x200,    0x400,    0x800,
//    0x1000,   0x2000,   0x4000,   0x8000,
//    0x10000,  0x20000,  0x40000,  0x80000,
//    0x100000, 0x200000, 0x400000, 0x800000,
//    0x1000000,0x2000000,0x4000000,0x8000000,
//};
// O(3^n)
template <typename T>
inline vector<T> naive_subset_zeta_transform(vector<T>& f) {
    const int MSK = f.size(); 
    const int n = 31 - __builtin_clz(MSK); 
    assert(MSK == (1<<n));
    vector<T> F(MSK);
    for (int msk = 0; msk < MSK; msk++) {
        F[msk] = f[0];
        for (int sub = msk; sub > 0; (sub-=1)&=msk) {
            F[msk] += f[sub];
        }
    }
    return F;
}
// O(n 2^n)
#define __loop(f) \
    const int MSK = f.size();\
    const int n = 31 - __builtin_clz(MSK);\
    assert(MSK == (1<<n));\
    for (int i = 0; i < n; i++)\
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

#define _Z fast_subset_zeta_transform
#define _M fast_subset_mobius_transform
#define _Zp fast_superset_zeta_transform
#define _Mp fast_superset_mobius_transform
#define _r map_complement
//template <typename Ring>
//inline void generalized_fast_subset_zeta_transform(vector<Ring>& f, function<void(Ring&,Ring)> add_assign) {
//}

// TODO convolution +(XuY=S, XcY=empty), relax one of. 
