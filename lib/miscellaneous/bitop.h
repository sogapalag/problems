#include <bits/stdc++.h>

using namespace std;

namespace bitop {
    // Warning: x = 0 may undefined behavior
    inline int ones(int x) { return __builtin_popcount(x); }
    inline int clz(int x) { return __builtin_clz(x); }
    inline int ctz(int x) { return __builtin_ctz(x); }
    inline int hbit(int x) { return 1<<(31-__builtin_clz(x)); }
    inline int lbit(int x) { return x&-x;}
    inline int& set1(int& x, int p) { return x |= 1<<p; }
    inline int& set0(int& x, int p) { return x &= ~(1<<p); }
    inline int& flip(int& x, int p) { return x ^= 1<<p; }
    inline bool isp2(int x) { return x && !(x&(x-1)); }
    inline bool ck(int x, int p) { return x>>p&1; }

    inline int ones_64(int64_t x) { return __builtin_popcountll(x); }
    inline int clz_64(int64_t x) { return __builtin_clzll(x); }
    inline int ctz_64(int64_t x) { return __builtin_ctzll(x); }
    inline int64_t hbit_64(int64_t x) { return 1ll<<(63-__builtin_clzll(x)); }
    inline int64_t lbit_64(int64_t x) { return x&-x;}
    inline int64_t& set1_64(int64_t& x, int p) { return x |= 1ll<<p; }
    inline int64_t& set0_64(int64_t& x, int p) { return x &= ~(1ll<<p); }
    inline int64_t& flip_64(int64_t& x, int p) { return x ^= 1ll<<p; }
    inline bool isp2_64(int64_t x) { return x && !(x&(x-1)); }
    inline bool ck_64(int64_t x, int p) { return x>>p&1; }
}
using namespace bitop;
