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
void solve() {
    int n; cin >> n;
    map<int,int> p;
    for (int _ = 0; _ < n; _++) {
        int i,j;
        cin >> i >> j;
        auto it = p.find(i);
        auto jt = p.find(j);
        if (it == p.end()) p[i] = i, it = p.find(i);
        if (jt == p.end()) p[j] = j, jt = p.find(j);
        swap(it->second, jt->second);
    }
    vector<int> is, xs;
    for (auto& _: p) {
        int i,x;
        tie(i,x) = _;
        is.push_back(i);
        xs.push_back(x);
    }

    n = is.size();
    ll res = 0;
    for (int _ = 0; _ < n; _++) {
        int i = is[_], x = xs[_];
        if (x < i) {
            int k = lower_bound(is.begin(), is.end(), x) - is.begin();
            res += i-x - (_ - k); // - #hole in [x..i)
        }
        if (x > i) {
            int k = upper_bound(is.begin(), is.end(), x) - is.begin();
            res += x-i - (k - _ - 1); // - #hole in (i..x]
        }
    }
    reverse(xs.begin(), xs.end());
    res += partial_ord_2d(xs);
    cout << res;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}
