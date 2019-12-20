#include <bits/stdc++.h>

using namespace std;

using u64=unsigned long long ;

u64 mod_mul(u64 x, u64 y, u64 m) {
    if (__builtin_clzll(x)+__builtin_clzll(y) >= 64) {
        x *= y;
        return (x>=m? x%m : x);
    } else {
        //return (__uint128_t)x*y %m;
    }
}

u64 mod_pow(u64 x, u64 e, u64 m) {
    u64 res = 1;
    for (; e; e >>= 1) {
        if (e & 1) res = mod_mul(res, x, m);
        x = mod_mul(x, x, m);
    }
    return res;
}
const int P = 1e9+7; 

void solve() {
    int p,k;
    cin >> p >> k;
    if (k==0) {
        cout << mod_pow(p, p-1, P);
    }else if(k==1) {
        cout << mod_pow(p, p, P);
    }else{
        u64 pw = k;
        int e;
        for (e = 1; e < p; e++) {
            if (pw == 1) break;
            (pw*=k)%=p;
        }
        cout << mod_pow(p, (p-1)/e, P);
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
