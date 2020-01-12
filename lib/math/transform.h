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


// SNIPPETS_START transform_set
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
// F_r[X] = sum_{S sub X, |S|=r} f[S]
template <typename T>
inline void fast_ranked_subset_zeta_transform(vector<T>& f, int r) {
    int n = 31 - __builtin_clz((int)f.size());
    int MSK = 1<<n;
    for (int msk = 0; msk < MSK; msk++) {
        if (__builtin_popcount(msk) != r) f[msk] = 0;
    }
    fast_subset_zeta_transform(f);
}
// F[r] = F_r
template <typename T>
inline vector<vector<T>> get_all_ranked_subset_zeta_transform(const vector<T>& f) {
    int n = 31 - __builtin_clz((int)f.size());
    int MSK = 1<<n;
    vector<vector<T>> F(n+1, vector<T>(MSK));
    for (int msk = 0; msk < MSK; msk++) {
        F[__builtin_popcount(msk)][msk] = f[msk];
    }
    for (int i = 0; i <= n; i++) {
        fast_subset_zeta_transform(F[i]);
    }
    return F;
}
// (f*g) (X) := sum_{U+V=X} f[U]g[V]. where + means direct sum, i.e. UuV=X, UcV=empty
// O(n^2 * 2^n) require O(n*2^n) space
// constant-coeff is larger than naive
// n  fast, naive
// 18  0.5  0.4
// 19  1.22 1.37
// 20  2.88 5.04
// Caution!! watch out over-flow
template <typename T>
inline void fast_subset_convolution_direct_sum(vector<T>& f, const vector<T>& g) {
    auto F = get_all_ranked_subset_zeta_transform(f);
    auto G = get_all_ranked_subset_zeta_transform(g);
    int n = 31 - __builtin_clz((int)f.size());
    int MSK = 1<<n;
    for (int r = n; r >= 0; r--) {
        for (int msk = 0; msk < MSK; msk++) {
            F[r][msk] *= G[0][msk];
            for (int i = 0; i < r; i++) {
                F[r][msk] += F[i][msk] * G[r-i][msk];
            }
        }
    }
    for (int i = 0; i <= n; i++) {
        fast_subset_mobius_transform(F[i]);
    }
    for (int msk = 0; msk < MSK; msk++) {
        f[msk] = F[__builtin_popcount(msk)][msk];
    }
}
// O(3^n) but with low constant
// Caution!! watch out over-flow
template <typename T>
inline void naive_subset_convolution_direct_sum(vector<T>& f, const vector<T>& g) {
    int n = 31-__builtin_clz((int)f.size());
    int MSK = 1<<n;
    for (int msk = MSK-1; msk >= 0; msk--) {
        f[msk] *= g[0];
        for (int sub = (msk-1)&msk; sub > 0; (sub-=1)&=msk) {
            f[msk] += f[sub] * g[sub^msk];
        }
        if(msk>0) f[msk] += f[0] * g[msk];
    }
}
// sum_{U+V=X} f[U]g[V]
template <typename T>
inline T get_point_value_subset_direct_sum(const vector<T>& f, const vector<T>& g, int msk) {
    T res = f[0] * g[msk];
    for (int sub = msk; sub > 0; (sub-=1)&=msk) {
        res += f[sub] * g[sub^msk];
    }
    return res;
}
// (f*g)[X] = sum_{UcV=empty, U,V sub X} f[U]g[V]
template <typename T>
inline void fast_subset_convolution_disjoin(vector<T>& f, vector<T>& g) {
    fast_subset_convolution_direct_sum(f, g);
    fast_subset_zeta_transform(f);
}
// f *_d g *_d 1. note f *_d 1 = Z(f)
template <typename T>
inline void _fast_subset_convolution_disjoin(vector<T>& f, vector<T>& g) {
    fast_subset_convolution_direct_sum(f, g);
    fill(g.begin(), g.end(), 1);
    fast_subset_convolution_direct_sum(f, g);
}
// sum_{UcV=empty, U,V sub X} f[U]g[V]
template <typename T>
inline T get_point_value_subset_disjoin(vector<T>& f, const vector<T>& g, int msk) {
    fast_subset_zeta_transform(f);
    return get_point_value_subset_direct_sum(f, g, msk);
}
// (f*g)[X] := sum_{UuV=X} f[U]g[V]
// aka. OR-convolution join
template <typename T>
inline void fast_subset_convolution_union(vector<T>& f, vector<T>& g) {
    fast_subset_zeta_transform(f);
    fast_subset_zeta_transform(g);
    int MSK = f.size();
    for (int i = 0; i < MSK; i++) {
        f[i] *= g[i];
    }
    fast_subset_mobius_transform(f);
}
// (f*g)[X] := sum_{UcV=X} f[U]g[V]
// aka. AND-convolution meet
template <typename T>
inline void fast_superset_convolution_intersection(vector<T>& f, vector<T>& g) {
    fast_superset_zeta_transform(f);
    fast_superset_zeta_transform(g);
    int MSK = f.size();
    for (int i = 0; i < MSK; i++) {
        f[i] *= g[i];
    }
    fast_superset_mobius_transform(f);
}

// O(2^n)
#define _r map_complement
// O(n2^n)
#define _Z fast_subset_zeta_transform
#define _M fast_subset_mobius_transform
#define _Zp fast_superset_zeta_transform
#define _Mp fast_superset_mobius_transform
#define _or_convo fast_subset_convolution_union
#define _and_convo fast_superset_convolution_intersection
#define _query_dsum get_point_value_subset_direct_sum
#define _query_disjoin get_point_value_subset_disjoin
#define _Zr fast_ranked_subset_zeta_transform
// O(n^2 2^n)
#define _all_Zr get_all_ranked_subset_zeta_transform
#define _dsum_convo fast_subset_convolution_direct_sum
#define _disjoin_convo fast_subset_convolution_disjoin

// when pow, note M(A*...e) = ZA...e
// when convo multi, M(ABC...) = ZA ZB ZC...
// Caution!!: for convolution, be careful overflow, &f should != &g (inplace modify)

//template <typename Ring>
//inline void generalized_fast_subset_zeta_transform(vector<Ring>& f, function<void(Ring&,Ring)> add_assign) {
//}
// SNIPPETS_END
