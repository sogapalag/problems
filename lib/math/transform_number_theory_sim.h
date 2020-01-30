#include <bits/stdc++.h>

using namespace std;

// SNIPPETS_START transform_number_theory_sim
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
// SNIPPETS_END
