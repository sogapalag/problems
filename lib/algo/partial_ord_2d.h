#include <bits/stdc++.h>

using namespace std;
using ll=long long; 
// #i<j, ai<aj, e.g. rev-version inversion.
ll partial_ord_2d(vector<int>& a) {
    ll res = 0;
    function<void(int,int)> divi = [&](int l, int r){
        if (r-l <= 1) return;
        int m = (l+r)>>1;
        divi(l, m); divi(m, r);
        for (int j = m, i = l; j < r; j++) {
            while (i < m && a[i] < a[j]) i++;
            res += i - l;
        }
        inplace_merge(a.begin() + l, a.begin() + m, a.begin() + r);
    };
    divi(0, a.size());
    return res;
}
