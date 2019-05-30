#include <bits/stdc++.h>

using namespace std;

// when range [l, r), has property notP~P, want first P.
// when return r, means not found.
template <typename T>
T bs_first(T l, T r, function<bool (T)> f) {
    assert(l < r);
    T mid;
    while (l != r) {
        mid = (l+r)/2;
        if (f(mid)) {
            r = mid;
        }else {
            l = mid + 1;
        }
    }
    return r;
}

// one can prove \E board, left (1,2k), (2,2k-1).. sum < M
//                         right. ... sum >= M
// this comb is optimal.
void solve() {
    int n, m;
    cin >> n >> m;
    vector<int> a(n<<1);
    for (auto& x: a) {
        cin >> x;
    }
    sort(a.begin(), a.end());
    int board = bs_first<int>(0, n+1, [&](int x){
            int l = 2*x, r = 2*n-1;
            while (l < r) {
                if (a[l] + a[r] < m) return false;
                l++; r--;
            }
            return true;
            });
    int l = 0, r = 2*board-1;
    int res = 0;
    while (l < r) {
        res = max(res, a[l]+a[r]);
        l++; r--;
    }
    l = 2*board, r = 2*n-1;
    while (l < r) {
        res = max(res, a[l]+a[r]-m);
        l++; r--;
    }
    cout << res;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
