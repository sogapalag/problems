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

int cnt(int lim, int x) {
    int res = 0;
    for (int i = 1; i <= lim; i++) {
        if(__gcd(i,x)==1)res+=lim/i;
    }
    return res;
}

// by http://rng.gozaru.jp/b.pdf
// sum coprime(i,j,k) [a/i]*[b/j]*[c/k]
// let g = gcd(j,k), recall 839f. first get F[d]= sum d|g,
//   then f[1] = mu[g]*F[g]
void solve() {
    int a,b,c;
    cin >> a >> b >> c;
    int res = 0;
    for (int i = 1; i <= a; i++) {
        int n = min(b,c);
        vector<int> f(n+1);
        for (int g = 1; g <= n; g++) {
            if (__gcd(i,g)==1){
                f[g] = cnt(b/g,i)*cnt(c/g,i);
            }
        }
        mobius_p(f);
        res += (a/i) * f[1];
    }
    res &= (1<<30)-1;
    cout << res;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
