#include <bits/stdc++.h>

using namespace std;

using ll=long long ;
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
void solve() {
    auto q = [](ll x)->bool{
        cout << "? " << x << endl;
        char y; cin >> y;
        return y == 'Y';
    };
    auto p = [](ll x){
        cout << "! " << x << endl;
    };
    const int N = 1000'000'000; 
    if (q(N)) {
        int k = bs_first<int>(0, 10, [&](int k){
                return q(2*pow(10,k));
                });
        p(pow(10, k));
    } else {
        int k = bs_first<int>(1, 10, [&](int k){
                return !q(pow(10,k));
                });
        int n = bs_first<int>(pow(10,k-1)+1, pow(10,k), [&](int n){
                return q(10ll*n);
                });
        p(n);
    }

}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
