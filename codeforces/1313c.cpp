#include <bits/stdc++.h>

using namespace std;

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
using ll=long long;
void solve() {
    int n; cin >> n;
    vector<int> a(n);
    for (auto& x: a) {
        cin >> x;
    }
    auto L = get_dominating_left(n, [&](int l, int i){return a[l] > a[i];});
    auto R = get_dominating_right(n, [&](int r, int i){return a[r] >= a[i];});
    vector<ll> dpl(n + 1), dpr(n + 1);
    for (int i = 0; i < n; i++) {
        dpl[i+1] = dpl[L[i]] + a[i] * 1ll * (i - L[i]+1);
    }
    for (int i = n-1; i >= 0; i--) {
        dpr[i] = dpr[R[i]+1] + a[i] * 1ll * (R[i]-i+1);
    }
    ll mx = 0; int k = -1;
    for (int i = 0; i < n; i++) {
        if (dpl[i+1] + dpr[i] - a[i] > mx) {
            mx = dpl[i+1] + dpr[i] - a[i];
            k = i;
        }
    }
    for (int i = k-1; i >= 0; i--) {
        a[i] = min(a[i+1], a[i]);
        mx -= a[i];
    }
    for (int i = k+1; i < n; i++) {
        a[i] = min(a[i-1], a[i]);
        mx -= a[i];
    }
    mx -= a[k];
    assert(mx == 0);
    for (auto& x: a) {
        cout << x << ' ';
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}
