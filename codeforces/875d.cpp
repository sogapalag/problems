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
// idiom, fix some max, it by</> L/R, by subset, subl/r
//   apparantly at least cross one subx
void solve() {
    int n; cin >> n;
    vector<int> a(n);
    for (auto& x: a) {
        cin >> x;
    }
    auto L = get_dominating_left(n, [&](int l, int i){
            return a[l] < a[i];
            });
    auto R = get_dominating_right(n, [&](int r, int i){
            return a[r] <= a[i];
            });
    auto subl = get_dominating_left(n, [&](int l, int i){
            return a[l] < a[i] && (a[l]|a[i]) <= a[i];
            });
    auto subr = get_dominating_right(n, [&](int r, int i){
            return a[r] <= a[i] && (a[r]|a[i]) <= a[i];
            });
    
    ll res = n*1ll*(n+1)/2;
    for (int i = 0; i < n; i++) {
        //res += (i-L[i]+1) * 1ll * (R[i]-i+1); // sum = n*(n+1)/2
        res -= (i-subl[i]+1) * 1ll * (subr[i]-i+1);
    }
    cout << res;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}
