#include <bits/stdc++.h>
#include "gondola.h"

using namespace std;

const int MOD = 1000000009; // 998244353; // 998244853; 
using u64=unsigned long long ;

u64 mod_mul(u64 x, u64 y, u64 m) {
    return x*y%m;
    //if (__builtin_clzll(x)+__builtin_clzll(y) >= 64) {
    //    x *= y;
    //    return (x>=m? x%m : x);
    //} else {
    //    return (__uint128_t)x*y %m;
    //}
}

u64 mod_pow(u64 x, u64 e, u64 m) {
    u64 res = 1;
    for (; e; e >>= 1) {
        if (e & 1) res = mod_mul(res, x, m);
        x = mod_mul(x, x, m);
    }
    return res;
}
// those a<=n, should has same token=a-i
int valid(int n, int a[]) {
    //vector<int> cnt(250005);
    int token = -1;
    //int lack = 0;
    //int mx = n;
    for (int i = 0; i < n; i++) {
        //if (++cnt[a[i]] > 1) return 0; // ensure distinct
        if (a[i] <= n) {
            int x = (a[i] - i + n) % n;
            if (token == -1) token = x;
            else if (token != x) return 0;
        } else {
            //lack++;
            //mx = max(mx, a[i]);
        }
    }
    sort(a, a+n);
    for (int i = 1; i < n; i++) {
        if (a[i-1] == a[i]) return 0;
    }
    return 1;
}
int replacement(int n, int a[], int res[]) {
    int token = 1;
    vector<pair<int, int>> need;
    for (int i = 0; i < n; i++) {
        if (a[i] <= n) {
            token = (a[i]-i+n)%n;
        } else {
            need.emplace_back(a[i], i);
        }
    }
    if (need.empty()) return 0;
    sort(need.begin(), need.end());
    int m = need.size();
    int l = 0;
    for (int _ = 0, x = n; _ < m; _++) {
        int y = need[_].first, i = need[_].second;
        i += token; if (i>n) i-=n;
        // repeat replace
        while (x < y) {
            res[l++] = i;
            i = ++x;
        }
    }
    return l;
}

// for each x, its final pos is fixed, prev (x-las-1) can in remain m-_
int countReplacement(int n, int a[]) {
    if (!valid(n, a)) return 0;
    vector<int> need;
    for (int i = 0; i < n; i++) {
        if (a[i]>n) need.emplace_back(a[i]-n);
    }
    sort(need.begin(), need.end());
    int m = need.size();
    int las = 0;
    int res = m == n ? n : 1; // n-shift possible
    for (int _ = 0; _ < m; _++) {
        int x = need[_];
        res = mod_mul(res, mod_pow(m-_, x-las-1, MOD), MOD);
        las = x;
    }
    return res;
    //mint res = 1;
    //for (int _ = 0; _ < m; _++) {
    //    int x = need[_];
    //    res *= mint(m-_).exp(x - las - 1);
    //    las = x;
    //}
    //return (int)res;
}
