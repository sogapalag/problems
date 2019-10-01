#include <bits/stdc++.h>

using namespace std;
using ll=long long;

template <typename T=int>
struct Rmq {
    vector<T> raw;
    static const int LOG = 17; // 20;
    int k;
    int n;
    vector<int> st[LOG];
    Rmq(vector<T> _v) { // pass in vec[0, n)
        raw = _v;
        n = raw.size();
        k = 32 - __builtin_clz(n);
        for (int j = 0; j < k; j++) {
            st[j].resize(n);
        }
        build();
    }
    inline int comp(int x, int y) { // DO! > max
        return raw[x] > raw[y] ? x : y;
    }
    void build() {
        for (int i = 0; i < n; i++) {
            st[0][i] = i;
        }
        for (int j = 1; j < k; j++) {
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
        return raw[query_id(l, r)];
    }
};

const int N = 5005; 
ll d[N][N];

void solve() {
    int n,m;
    cin >> n >> m;
    vector<ll> a(n);
    a[0] = 0;
    for (int i = 1; i < n; i++) {
        cin >> a[i];
        a[i] += a[i-1];
    }

    vector<vector<int>> b(m, vector<int>(n));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cin >> b[j][i];
        }
    }

    for (int j = 0; j < m; j++) {
        Rmq<> R(b[j]); // rmq is easy to understand. there is method use stack maintain dec. chain.
        function<void(int,int)> update = [&](int l, int r){
            if (l >= r) return;
            int i = R.query_id(l, r);
            // in japan, called imos-method, english?
            // x contribute when left [l,i], right[i,r) form a rectangle on d.
            // + -
            // - + then only the rect. has the val.
            d[l +1][i +1] += b[j][i];
            d[i+1 +1][i +1] -= b[j][i];
            d[l +1][r +1] -= b[j][i];
            d[i+1 +1][r +1] += b[j][i];
            update(l, i);
            update(i+1, r);
        };
        update(0, n);
    }
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            d[i][j] += d[i][j-1]-d[i-1][j-1]+d[i-1][j];
        }
    }

    ll res = -(1ll<<60);
    for (int i = 0; i < n; i++) {
        for (int j = i; j < n; j++) {
            ll val = d[i+1][j+1] - (a[j]-a[i]);
            res = max(res, val);
        }
    }
    cout << res;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
