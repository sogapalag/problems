#include <bits/stdc++.h>

using namespace std;

// when range [l, r), has property notP~P, want first P.
// when return r, means not found.
template <typename T>
T bs_first(T l, T r, function<bool (T)> f) {
    assert(l < r);
    T mid;
    while (l != r) {
        mid = l + (r-l)/2;
        if (f(mid)) {
            r = mid;
        }else {
            l = mid + 1;
        }
    }
    return r;
}
using ll=long long ;
void solve() {
    int n, A,B;
    cin >> n >> A >> B;
    vector<int> a(n);
    for (auto& x: a) {
        cin >> x;
    }
    sort(a.begin(), a.end());
    const ll LIM = 1e9; 
    int res = bs_first<ll>(0, LIM+1, [&](ll t){
            ll rem = t;
            ll base = 1ll*B*t;
            ll ex = A-B;
            for (auto& x: a) {
                if (base >= x) continue;
                ll need = (x-base+ex-1)/ex;
                rem -= need;
                if (rem < 0) return false;
            }
            return true;
            });
    cout << res;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
