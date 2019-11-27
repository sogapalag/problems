#include <bits/stdc++.h>

using namespace std;

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
struct Trap {
    int l, r, d;
    Trap() {}
    Trap(int _l, int _r, int _d) : l(_l), r(_r), d(_d) {}
};
void solve() {
    int m,n,k,t;
    cin >> m >> n >> k >> t;
    vector<int> a(m);
    for (auto& x: a) {
        cin >> x;
    }
    sort(a.begin(), a.end());
    vector<Trap> b(k);
    for (int i = 0; i < k; i++) {
        int l,r,d;
        cin >> l >> r >> d;
        b[i] = {l,r,d};
    }
    // connected component segs, [l..r], cost (r-l+1)*2
    auto ck = [&](int x){
        x = a[m-x];
        int sum = n+1;
        vector<pair<int, int>> seg;
        for (int i = 0; i < k; i++) {
            if (b[i].d > x) {
                seg.emplace_back(b[i].l, b[i].r);
            }
        }
        sort(seg.begin(), seg.end());
        int l = 0, r = -1;
        for (auto& p: seg) {
            if (p.first <= r) {
                r = max(r, p.second);
            } else {
                sum += (r-l+1) * 2;
                l = p.first;
                r = p.second;
            }
        }
        sum += (r-l+1) * 2;
        return sum <= t;
    };
    int res = bs_last<int>(1, m+1, ck);
    cout << res;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
