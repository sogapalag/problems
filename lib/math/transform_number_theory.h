#include <bits/stdc++.h>

using namespace std;

#define __up_loop(f) \
    for (int n = f.size(), i = 1; i < n; i++)\
        for (int j = i; (j += i) < n;)
#define __dn_loop(f) \
    for (int n = f.size(), i = n-1; i >= 1; i--)\
        for (int j = i; (j += i) < n;)

template <typename T>
inline void zeta(vector<T>& f) {
    __dn_loop(f) f[j] += f[i];
}
template <typename T>
inline void mobius(vector<T>& F) {
    __up_loop(F) F[j] -= F[i];
}
template <typename T>
inline void zeta_p(vector<T>& f) {
    __up_loop(f) f[i] += f[j];
}
template <typename T>
inline void mobius_p(vector<T>& F) {
    __dn_loop(F) F[i] -= F[j];
}
// f*g [s] = sum_d|s f[d]g[s/d]
template <typename T>
inline void dirichlet_convolution(vector<T>& f, const vector<T>& g) {
    int n = f.size();
    for (int i = n-1; i >= 1; i--) {
        for (int j = i; (j += i) < n;) {
            f[j] += f[i] * g[j/i];
        }
        f[i] *= g[1];
    }
}
// f*g [l] = sum_l=lcm(x,y) f[x]g[y]
template <typename T>
inline void convolution_lcm(vector<T>& f, vector<T>& g) {
    zeta(f);
    zeta(g);
    int n = f.size();
    for (int i = 1; i < n; i++) {
        f[i] *= g[i];
    }
    mobius(f);
}
// f*g [g] = sum_g=gcd(x,y) f[x]g[y]
template <typename T>
inline void convolution_gcd(vector<T>& f, vector<T>& g) {
    zeta_p(f);
    zeta_p(g);
    int n = f.size();
    for (int i = 1; i < n; i++) {
        f[i] *= g[i];
    }
    mobius_p(f);
}
// Caution!! for convolution, watch out overflow, inplace that &f should != &g
