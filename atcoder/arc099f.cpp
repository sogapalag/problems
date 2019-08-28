#include <bits/stdc++.h>

using namespace std;

using ll=long long;

#define K 6 
#define rep(i) for(int i=0;i<K;i++)
using Token=array<int,K>;

//const ll R = 843823891, iR = 1040004855;
const ll R[K] = {3213,24289,34299,929923,438,42};
const ll iR[K] = {727200786, 1395409909, 1110851529, 35704193, 1005586100, 1598363886};

const ll M = 1637348371;
ll mpow(ll x, int64_t e) {
    ll res = 1;
    for (; e; e >>= 1) {
        if (e & 1) res *= x, res %= M;
        x *= x, x %= M;
    }
    return res;
}
ll minv(ll x) {
    return mpow(x, M-2);
}

struct Lm {
    ll k,b;
    Lm() {}
    Lm(ll _k,ll _b): k(_k),b(_b){}
    Lm(char x, int i) {
        if (x == '+') k = 1, b = 1;
        if (x == '-') k = 1, b = M-1;
        if (x == '>') k = R[i], b = 0;
        if (x == '<') k = iR[i],b = 0;
    }
    Lm(const Lm& _lm): k(_lm.k), b(_lm.b){}
    Lm& operator*=(const Lm& _lm){
        b += k*_lm.b%M; b %= M;
        k *= _lm.k; k %= M;
        return *this;
    }
    Lm inv(){
        ll ik = minv(k);
        ll ib = -ik*b; ib %= M; (ib+=M)%=M;
        return {ik,ib};
    }
    ll eval(ll x) {
        return (k*x%M+b)%M;
    }
};
Lm operator*(const Lm& _a, const Lm& _b) {
    return Lm(_a) *= _b;
}
void solve() {
    int n; cin >> n;
    string s; cin >> s;
    vector<Lm> a[K], ia[K];
    vector<Token> z(n+1), g(n);
    rep(k) {
        for (int i = 0; i < n; i++) {
            a[k].emplace_back(s[i], k);
            ia[k].emplace_back(a[k][i].inv());
        }
        auto isuf = ia[k];
        for (int i = n-2; i >= 0; i--) {
            isuf[i] = isuf[i+1] * isuf[i];
        }
        ll c = isuf[0].inv().eval(0);
        z[n][k] = 0;
        for (int i = 0; i < n; i++) {
            z[i][k] = isuf[i].eval(0);
            g[i][k] = isuf[i].eval(c);
        }
    }
    map<Token, int> cnt;
    ll res = 0;
    for (int i = 0; i < n; i++) {
        cnt[g[i]]++;
        res += cnt[z[i+1]];
    }
    cout << res;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
