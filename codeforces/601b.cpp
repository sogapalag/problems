#include <bits/stdc++.h>

using namespace std;
using ll=long long;
// should hold transitivity.
using PartialOrd = function<bool(int,int)>;
// f(x, i): x by(<) i
vector<int> get_dominating_left(int n, PartialOrd f) {
    assert(n > 0);
    vector<int> L(n);
    vector<int> stk;
    for (int i = 0; i < n; i++) {
        // some case might need check dominating itself here
        // if not dominating itself, L[i] = i + 1;
        while (!stk.empty() && f(stk.back(), i)) {
            stk.pop_back();
        }
        L[i] = stk.empty() ? 0 : stk.back() + 1;
        stk.push_back(i);
    }
    return L;
}
vector<int> get_dominating_right(int n, PartialOrd f) {
    assert(n > 0);
    vector<int> R(n);
    vector<int> stk;
    for (int i = n-1; i >= 0; i--) {
        // if not dominating itself, R[i] = i - 1;
        while (!stk.empty() && f(stk.back(), i)) {
            stk.pop_back();
        }
        R[i] = stk.empty() ? n-1 : stk.back() - 1;
        stk.push_back(i);
    }
    return R;
}
ll calc(vector<int>& a) {
    int n = a.size();
    auto L = get_dominating_left(n, [&](int l, int i){ return a[l]<a[i]; });
    auto R = get_dominating_right(n, [&](int r, int i){ return a[r]<=a[i]; });
    ll res = 0;
    for (int i = 0; i < n; i++) {
        res += a[i] * 1ll * (i-L[i]+1) * (R[i]-i+1);
    }
    return res;
}

// key: max Lipshitz must be some adj-index
// brute-force each query, since q~100. Bonus q~1e5?
void solve() {
    int n,q;
    cin >> n >> q;
    vector<int> a(n);
    for (auto& x: a) {
        cin >> x;
    }
    while (q--) {
        int l,r;
        cin >> l >> r;
        vector<int> b;
        for (int i = l; i < r; i++) {
            b.push_back(abs(a[i] - a[i-1]));
        }
        cout << calc(b) << '\n';
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}
