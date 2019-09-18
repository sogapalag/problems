#include <bits/stdc++.h>

using namespace std;

// SNIPPETS_START miller_rabin
using u64=unsigned long long ;

u64 mod_mul(u64 x, u64 y, u64 m) {
    if (__builtin_clzll(x)+__builtin_clzll(y) >= 64) {
        x *= y;
        return (x>=m? x%m : x);
    } else {
        return (__uint128_t)x*y %m;
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
// SNIPPETS_END
