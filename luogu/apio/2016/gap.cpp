#include <bits/stdc++.h>
#include "gap.h"
using namespace std;
using ll=long long;

// http://uoj.ac/problem/206
ll findGap(int T, int N){
    ll l = 0, r = 1e18;
    MinMax(l,r, &l,&r);
    if (N == 2) return r-l;
    if (T == 1) {
        ll mi, mx;
        ll res = 0;
        N -= 2;
        while (true) {
            MinMax(l+1, r-1, &mi, &mx);
            res = max(res, mi-l);
            res = max(res, r-mx);
            if (N <= 1) break;
            if (N <= 2) {
                res = max(res, mx-mi); break;
            }
            N -= 2;
            l = mi, r = mx;
        }
        return res;
    }
    ll d = (r-l-1)/(N-2) + 1; // ceil
    ll mi, mx;
    ll res = 0;
    ll las = l;
    for (ll i = l+1, j; i<r; i = j) {
        j = min(i+d, r);
        MinMax(i, j-1, &mi, &mx);
        if (mi == -1) continue;
        res = max(res, mi - las);
        las = mx;
    }
    res = max(res, r - las);
    return res;
}
