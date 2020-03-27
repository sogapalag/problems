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
using ll=long long;

const int N = 1000111; 
const int K = 2048; 
vector<int> mu(N);
vector<int> sum(N);
void prep() {
    mu[1] = 1; mobius(mu);
    for (int i = 1; i < N; i++) {
        sum[i] = sum[i-1] + mu[i];
    }
}
// sum of mu
map<int,int> memo;
int smu(int n){
    if (n < N) return sum[n];
    auto it = memo.find(n);
    if (it != memo.end()) return it->second;
    int res = 1;
    for (int l = 2, r; l <= n; l = r+1) {
        r = n/(n/l);
        res -= (r-l+1) * smu(n/l);
    }
    return memo[n] = res;
}
// F(n,k) := \sum_{i=[1..n]} mu(i) * [(i,k)=1]
//        := \sum_{d|k} mu^2(d) * F(n/d,d)
map<int,ll> mp[K];
ll F(int n, int k){
    if (n==0) return 0;
    if (k==1) return smu(n);
    auto it = mp[k].find(n);
    if (it != mp[k].end()) return mp[k][n];
    ll res = 0;
    for (int d = 1; d*d <= k; d++) {
        if (k%d==0) {
            if (mu[d]) res += F(n/d,d);
            if (d*d!=k && mu[k/d]) res += F(n/(k/d), k/d);
        }
    }
    return mp[k][n] = res;
}
// x/y first valid <=> x=x+k^p mod(y) <=> k^p=1 mod(y) <=> gcd(k,y)=1
// so res := sum_{i=[1..n],j=[1..m]} [(i,j)=1][(j,k)=1]
//        ... some simplification
//        := sum_{d=[1..min(n,m)]} mu(d) [(d,k)=1] (n/d) sum_{j=[1..m/d]}[(j,k)=1]
//        := {n/d contribute block, F(i,k)} * G(j)
// useful links
// https://oi-wiki.org/math/du/#_4
// https://www.cnblogs.com/PinkRabbit/p/NOI2016D1T3.html
// https://www.luogu.com.cn/problemnew/solution/P1587
void solve() {
    prep();
    int n, m, k;
    cin >> n >> m >> k;
    vector<int> sphi(k + 1);
    for (int i = 1; i <= k; i++) {
        sphi[i] = sphi[i-1] + (__gcd(i,k)==1);
    }
    // G(n) := \sum_{i=[1..n]} [(i,k)=1]
    auto G = [&](int n){
        return (n/k)*sphi[k] + sphi[n%k];
    };
    ll res = 0;
    ll crt=0,nxt;
    for (int l = 1, r; l <= n && l <= m; l = r+1) {
        r = min(n/(n/l), m/(m/l));
        nxt = F(r, k); // r
        res += (n/l) *1ll* (nxt-crt) * G(m/l);
        crt = nxt;
    }
    cout << res;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}
