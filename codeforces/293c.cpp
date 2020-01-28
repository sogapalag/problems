#include <bits/stdc++.h>

using namespace std;

using u64=unsigned long long ;

u64 mod_mul(u64 x, u64 y, u64 m) {
    if (__builtin_clzll(x)+__builtin_clzll(y) >= 64) {
        x *= y;
        return (x>=m? x%m : x);
    } else {
        return 0;//(__uint128_t)x*y %m;
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

// [0, 2^32) 0.2 sec / 10^6.
// [0, 2^64) 1.3 sec / 10^6
// pass u32/u64 plz, avoid potential negative.
bool miller_rabin(u64 p) {
    static pair<u64, valarray<u64>> WIT[] = {
        {2'046, {2}},
        {1'373'652, {2, 3}},
        {9'080'190, {31, 73}},
        {25'326'000, {2, 3, 5}},
        {4'759'123'140, {2, 7, 61}},
        {1'112'004'669'632, {2, 13, 23, 1662803}},
        {2'152'302'898'746, {2, 3, 5, 7, 11}},
        {3'474'749'660'382, {2, 3, 5, 7, 11, 13}},
        {341'550'071'728'320, {2, 3, 5, 7, 11, 13, 17}},
        {0xFFFF'FFFF'FFFF'FFFF, {2, 3, 5, 7, 11, 13, 17, 19, 23}}};

    if (p%2 == 0) return p==2;
    if (p == 1) return false;
    u64 d = p - 1, e = 0;
    while (d%2 == 0) d/=2, e++;
    int _k = 0;
    while (WIT[_k].first < p) _k++;
    for (const auto& a: WIT[_k].second) {
        u64 t = mod_pow(a, d, p);
        if (t == 1 || t == p-1) continue;
        bool ok = false;
        for (size_t _ = 0; _ < e; _++) {
            t = mod_mul(t, t, p);
            if (t == 1) return false;
            if (t == p-1) {ok=true; break;}
        }
        if (ok) continue;
        else return false;
    }
    return true;
}
u64 mod_add(u64 x, u64 y, u64 m) {
    x += y;
    return x>=m? x-m: x;
}

u64 pollard_rho(u64 n, u64& c) {
    auto f = [&](u64 t){
        return mod_add(mod_mul(t,t,n), c, n);
    };
    while(true){
        u64 x=2, y=2;
        u64 d=1;
        while (d == 1) {
            x = f(x);
            y = f(f(y));
            d = __gcd(x<y?y-x:x-y, n);
        }
        if (d == n) {
            c++; continue;
        }
        return d;
    }
}

// [1, 2^64) 0.3 sec / 10^3
// [1, 2^32) 0.4 sec / 10^5
vector<pair<u64,u64>> factor(u64 n) {
    assert(n != 0);
    vector<pair<u64,u64>> res;
    static u64 WHEEL[] = {2, 3, 5, 7, 11, 13};
    for (const auto& p: WHEEL) {
        if (n%p == 0) {
            u64 e = 0;
            while (n%p == 0) {
                n /= p; e++;
            }
            res.emplace_back(p, e);
        }
    }
    if (n == 1) return res;

    vector<u64> pool;
    map<u64, u64> cnt;
    pool.emplace_back(n);
    u64 c = 1;
    while (!pool.empty()) {
        u64 n = pool.back(); pool.pop_back();
        if (miller_rabin(n)) {
            cnt[n]++; continue;
        }
        u64 d = pollard_rho(n, c);
        pool.emplace_back(d);
        pool.emplace_back(n/d);
    }
    for (auto& p: cnt) {
        res.push_back(p);
    }
    return res;
}
#undef LOCAL
string to_string(string s) { return '"' + s + '"'; }
string to_string(bool x) { return (x ? "T" : "F"); }
string to_string(const char* s) { return to_string((string)s); }
template <typename A, typename B>
string to_string(pair<A, B> p) { return "(" + to_string(p.first) + ", " + to_string(p.second) + ")"; }
template <typename V>
string to_string(V v) {
    bool f = true; string res = "[";
    for (const auto& x: v) {
        if (!f) res += ", ";
        f = false;
        res += to_string(x); } res += "]";
    return res;
}
void debug() { cerr << endl; }
template <typename H, typename... T>
void debug(H h, T... t) { cerr << " " << to_string(h); debug(t...); }
#ifdef LOCAL
#define dbg(args...) cerr<<"("<<#args<<") =", debug(args)
#else
#define dbg(args...) 2020
#endif


void solve() {
    u64 n; cin >> n;
    if (n%3!=0) {
        cout << 0; return;
    }
    n/=3;

    vector<u64> ds;
    //ds.emplace_back(1);
    //for (auto& p: factor(n)) {
    //    u64 b, e;
    //    tie(b, e) = p;
    //    int sz = ds.size();
    //    u64 y = 1;
    //    while (e--) {
    //        y *= b;
    //        for (int i = 0; i < sz; i++) {
    //            ds.emplace_back(ds[i] * y);
    //        }
    //    }
    //}
    for (u64 d = 1; d*d <= n; d++) {
        if (n % d == 0) {
            ds.push_back(d);
            if (n/d != d) ds.push_back(n/d);
        }
    }
    sort(ds.begin(), ds.end());
dbg(ds);
    u64 INF = 1e18;
    auto ckmul = [&](u64& x, u64 y){
        if (x >= INF/y) x = INF;
        else x *= y;
    };
    u64 res = 0;
    // 3(a+b)(a+c)(b+c) = n. x+y>z s.t. a>0
    for (u64 x: ds) {
        u64 x3 = x;
        ckmul(x3,x); ckmul(x3,x);
        if (x3 > n) break;  // x<=y
        u64 yz = n / x;
        for (u64 y: ds)if(y>=x && yz%y==0 && x+y > yz/y) {
            u64 y2 = y;
            ckmul(y2,y);
            if (y2 > yz) break; // y<=z
            u64 z = yz/y;
            if ((x^y^z)&1) continue; // (x+y-z)=2a
dbg(x,y,z);
            if (x<y&&y<z) res += 6;
            else if (x==y&&y==z) res += 1;
            else res += 3;
        }
    }
    cout << res;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}
