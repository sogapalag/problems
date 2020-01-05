#include <bits/stdc++.h>

using namespace std;
using ll=long long;

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
const int N = 100005; 
void solve() {
    int n; ll K;
    cin >> n >> K;
    vector<pair<int, int>> a(n);
    for (int i = 0; i < n; i++) {
        int x,y;
        cin >> x >> y;
        a[i]={x,y};
    }
    sort(a.begin(), a.end());

    auto ck = [&](int d){
        ll cnt = 0;
        Fenwick<int> f(N);
        for (auto& p: a) {
            f.add(p.second, 1);
        }
        for (int i = 0, j = i; i < n; i++) {
            j = max(j, i);
            while (j < n && a[j].first - a[i].first <= d) {
                f.add(a[j].second, -1);
                j++;
            }
            cnt += j-i-1;
            int l = max(1, a[i].second - d);
            int r = min(N, a[i].second + d);
            cnt += f.query(l, r);
        }
        return cnt >= K;
    };
    int D = bs_first<int>(0, N, ck);
    cout << D;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
