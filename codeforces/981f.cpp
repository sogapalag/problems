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

// first note optim-form is a shift 1to1.
// b -L, +L. for impl avoid anti-cycle %L
// then greedy l/r boarder, check whether a valid seg.
void solve() {
    int n, L;
    cin >> n >> L;
    vector<int> a(n), b(3*n);
    for (auto& x: a) {
        cin >> x;
    }
    for (int i = 0; i < n; i++) {
        cin >> b[i];
        b[i+n] = b[i]-L;
        b[i+2*n]=b[i]+L;
    }
    sort(a.begin(), a.end());
    sort(b.begin(), b.end());

    auto ck = [&](int x){
        int l = 0, sl = -1e8;
        int r = 3*n-1, sr = 1e8;
        for (int i = 0; i < n; i++) {
            while (a[i] - b[l] > x) {
                l++;
            }
            while (b[r] - a[i] > x) {
                r--;
            }
            // shift
            sl = max(sl, l - i);
            sr = min(sr, r - i);
            l++; r++; // nxt i match
        }
        // valid segs
        return sl <= sr;
    };
    int res = bs_first<int>(0, L+1, ck);
    cout << res;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
