#include <bits/stdc++.h>

using namespace std;

const int L = 29; 

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
    int n; cin >> n;
    vector<int> a(n);
    for (auto& x: a) {
        cin >> x;
    }
    vector<int> sum(n + 1);
    auto prep = [&](int j){
        for (int i = 0; i < n; i++) {
            int x = a[i]>>j&1;
            sum[i + 1] = sum[i] + x;
        }
    };
    auto cnt1 = [&](int l, int r){
        return sum[r] - sum[l];
    };
    auto cnt0 = [&](int l, int r){
        return r-l - cnt1(l,r);
    };
    int res = 0;
    for (int j = 0; j < L; j++) {
        const int MSK = 1<<j; 
        const int R = MSK-1; 
        if(j)sort(a.begin(), a.end(), [&](auto& u, auto& v){
            return (u&R) < (v&R);
        });
        prep(j);
        int z = 0;
        //for (int i = 1; i < n; i++) {
        //    int x = a[i]>>j&1;
        //    int l = bs_first<int>(0, i, [&](int l){
        //            return (a[l]&R) + (a[i]&R) >= MSK;
        //            });
        //    if (x) {
        //        z ^= cnt0(0, l)&1;
        //        z ^= cnt1(l, i)&1;
        //    } else {
        //        z ^= cnt1(0, l)&1;
        //        z ^= cnt0(l, i)&1;
        //    }
        //}
        // [l..i) has carry
        for (int i = n-1, l = 0; i >= 1; i--) {
            int x = a[i]>>j&1;
            while (l < i && (a[l]&R) + (a[i]&R) < MSK ) {
                l++;
            }
            if (l > i) l = i;
            if (x) {
                z ^= cnt0(0, l)&1;
                z ^= cnt1(l, i)&1;
            } else {
                z ^= cnt1(0, l)&1;
                z ^= cnt0(l, i)&1;
            }
        }
        if (z) res |= 1<<j;
    }
    cout << res;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}
