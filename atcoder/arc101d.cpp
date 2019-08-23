#include <bits/stdc++.h>

using namespace std;
using ll=long long ;

template <typename T=int>
struct Fenwick {
    int n;
    vector<T> v;
    
    Fenwick(int size = 100005) : n(size), v(n+1, 0) {}
    inline void add(int p, T val) {
        for (; p <= n; p += (p&-p)) { v[p] += val; }
    }
    inline T query(int p) {
        T tmp = 0;
        for (; p > 0; p -= (p&-p)) { tmp += v[p]; }
        return tmp;
    }
    inline T query(int l, int r) {
        return query(r) - query(l-1);
    }
};

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

// med: [#>=med] >= (TOT+1)/2
// for med >= x, iff #>=x > (m+1)/2 iff sum >= 0. +1(>=x) -1(<x) iff prefix sum cmp inversions count
void solve() {
    int n; cin >> n;
    ll TOT = (ll)n*(n+1)/2;
    vector<int> a(n);
    for (auto& x: a) {
        cin >> x;
    }
    // # m_l..r >= med
    auto ge = [&](int med){
        auto b = a;
        int sum = n+5;
        for (auto& x: b) {
            x = sum += (x>=med ? 1:-1);
        }
        Fenwick<int> f(2*n+10);
        f.add(n+5, 1);
        ll res = 0;
        for (int x: b) {
            res += f.query(x);
            f.add(x, 1);
        }
        return res;
    };
    auto candi = a;
    sort(candi.begin(), candi.end());
    candi.erase(unique(candi.begin(), candi.end()), candi.end());
    int m = candi.size();
    int res = bs_last<int>(0, m, [&](int i){
            return ge(candi[i]) >= (TOT+1)/2;
            });
    cout << candi[res];
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
