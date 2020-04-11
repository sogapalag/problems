#include <bits/stdc++.h>
#include "boxes.h"

using namespace std;
using ll=long long;

ll __delivery(int n, int k, int L, int pos[]) {
    int H = L/2;
    ll base = 0;
    vector<int> a[2];
    for (int i = 0; i < n; i++) {
        if (pos[i] <= H) a[0].push_back(pos[i]);
        else a[1].push_back(L - pos[i]);
    }
    reverse(a[1].begin(), a[1].end());
    for (int _:{0,1}) {
        int s = a[_].size()/k*k;
        vector<int> b = vector<int>(a[_].begin()+s, a[_].end());
        // WA, if r is max return-point, should greedy down, i.e. r-k, r-2k, ...
        // 10 5 1000
        // 7 63 166 821 853 857 930 934 989 995
        // 712 . 976
        while (s > 0) {
            base += a[_][s-1]; s-=k;
        }
        a[_] = b;
    }
    ll res = base * 2;
    if (a[0].empty()) {
        if (!a[1].empty()) {
            res += a[1].back()*2;
        }
    } else if (a[1].empty()) {
        res += a[0].back()*2;
    } else {
        // use L
        ll tmp = L;
        int i = a[0].size() + a[1].size() - k;
        if (i > 0) {
            tmp += 2*min(a[0][i-1], a[1][i-1]);
        }
        // not
        tmp = min(tmp, (a[0].back()+a[1].back()) * 2ll);
        res += tmp;
    }
    return res;
}
const int N = 1e7+10; 
ll dp[2][N];

// first one can guess the nontrivial optim-form is like
// some come&go(ca or ac), then final whole L.   a(anti) c(clock)
// proof of at most one L, if >=2, then we can always use some half to come&go, won't be worse then.
// note for a half a[0], once we dicide the right-most use come&go, then optim is greedy pick most k
// so r, r-k, r-2k,.., which can prep by dp.
// then note we using L, we obvious remove some suffix of a0/a1, just iter any valid suffix

ll delivery(int n, int k, int L, int pos[]) {
    int H = L/2;
    vector<int> a[2];
    for (int i = 0; i < n; i++) {
        if (pos[i] <= H) a[0].push_back(pos[i]);
        else a[1].push_back(L - pos[i]);
    }
    reverse(a[1].begin(), a[1].end());
    for (int _:{0,1}) {
        int m = a[_].size();
        for (int i = 0; i < m; i++) {
            dp[_][i+1] = (i-k>=0 ? dp[_][i-k+1] : 0) + 2*a[_][i];
        }
    }
    ll res = dp[0][a[0].size()] + dp[1][a[1].size()];
    int m = a[0].size();
    for (int i = 1; i < k && i <= m; i++) {
        ll tmp = L;
        tmp += dp[0][m-i];
        tmp += dp[1][max(0, (int)a[1].size() - (k-i))];
        res = min(res, tmp);
    }
    return res;
}
