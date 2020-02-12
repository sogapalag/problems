#include <bits/stdc++.h>

using namespace std;

template <typename T=int>
struct Rmq {
    vector<T> a;
    int n, L;
    vector<vector<int>> st;
    Rmq(vector<T> _a) : a(_a) { // pass in vec[0, n)
        n = a.size();
        build();
    }
    inline int comp(int x, int y) { // DO! > max
        return a[x] > a[y] ? x : y;
    }
    void build() {
        L = 32 - __builtin_clz(n);
        st.resize(L);
        for (int j = 0; j < L; j++) {
            st[j].resize(n);
        }
        for (int i = 0; i < n; i++) {
            st[0][i] = i;
        }
        for (int j = 1; j < L; j++) {
            for (int i = 0; i + (1<<j) <= n; i++) {
                st[j][i] = comp(st[j-1][i], st[j-1][i + (1<<(j-1))]);
            }
        }
    }
    // [l, r)
    inline int query_id(int l, int r) {
        assert(0 <= l && l < r && r <= n);
        int j = 31 - __builtin_clz(r - l);
        return comp(st[j][l], st[j][r - (1<<j)]);
    }
    inline T query(int l, int r) {
        return a[query_id(l, r)];
    }
};
using ll=long long;

// key: relation is using nxt which can go furthest
void solve() {
    int n; cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n-1; i++) {
        cin >> a[i]; a[i]--;
    }a[n-1] = n-1;
    Rmq<> rmx(a);

    vector<ll> dp(n);
    ll sum = 0;
    for (int i = n-2; i >= 0; i--) {
        int x = a[i];
        int m = rmx.query_id(i+1, x+1);
        dp[i] = dp[m] + n-1-i - (x - m);
        sum += dp[i];
    }
    cout << sum;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}
