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
// when range [l, r), has property P~notP, want last P.
// when return l-1, means not found.
template <typename T>
T bs_last(T l, T r, function<bool (T)> f) {
    assert(l < r);
    T mid;
    while (l != r) {
        mid = l + (r-l)/2;
        if (f(mid)) {
            l = mid + 1;
        }else {
            r = mid;
        }
    }
    return r-1;
}

int erdos_gallai(const vector<int>& a, int val) {
    int n = a.size();
    long long L = 0, R = 0;
    for (int i = n-1, j = 0, k = 1; i >= 0; i--, k++) {
        L += a[i];
        while (j < i && a[j] < k) {
            R += a[j++];
        }
        while (j > i) {
            R -= a[--j];
        }
        if (L - k*1ll*(k-1) > R + (i-j)*1ll*k) return a[i]<=val ? 1 : -1;
    }
    return 0;
}

void solve() {
    int n; cin >> n;
    vector<int> A(n);
    int p = 0;
    for (auto& x: A) {
        cin >> x;
        p ^= x;
    }p&=1;
    sort(A.begin(), A.end());

    int l = bs_first<int>(0, n, [&](int k){
            auto a = A;
            a.insert(upper_bound(a.begin(), a.end(), 2*k+p), 2*k+p);
            return erdos_gallai(a, 2*k+p) >= 0;
            });
    int r = bs_last<int>(0, n, [&](int k){
            auto a = A;
            a.insert(upper_bound(a.begin(), a.end(), 2*k+p), 2*k+p);
            return erdos_gallai(a, 2*k+p) <= 0;
            });
    if (l > r) {
        cout << -1;
    } else {
        for (int i = l; i <= r; i++) {
            cout << 2*i+p << ' ';
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}
