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

// matain lists largest in down sort.
// replace first i, that val > a_i
//
// another method. recall Dilworth's theorem.
// ans = len of longest decreasing(>=) sequence.
void solve() {
    int n; cin >> n;
    vector<int> down;  down.reserve(n+1);
    down.push_back(1000'000'111);
    for (int _ = 0; _ < n; _++) {
        int x; cin >> x;
        if (x <= down.back()) {
            down.push_back(x);
        }else{
            int sz = down.size();
            int i = bs_first<int>(0, sz, [&](int i){
                    return x > down[i];
                    });
            down[i] = x;
        }
    }
    int res = down.size()-1;
    cout << res;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
