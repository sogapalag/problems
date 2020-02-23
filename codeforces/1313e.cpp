#include <bits/stdc++.h>

using namespace std;

// z[i] = len of lcp of s, s[i..]; lcp(longest common prefix)
vector<int> z_fn(const string& s) {
    int n = s.size();
    vector<int> z(n, 0);
    for (int i = 1, l = 0, r = 0; i < n; i++) {
        if (i <= r)
            z[i] = min(r-i+1, z[i-l]);
        while (i+z[i] < n && s[z[i]] == s[i+z[i]]) {
            z[i]++;
        }
        if (i+z[i]-1 > r) {
            l = i; r = i+z[i]-1;
        }
    }
    return z;
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
using ll=long long;
void solve() {
    int n,m;
    cin >> n >> m;
    string a,b,s;
    cin >> a >> b >> s;
    auto za = z_fn(s.substr(0, m-1) + "#" + a);
    za = vector<int>(za.begin()+m, za.end());

    reverse(s.begin(), s.end());
    reverse(b.begin(), b.end());
    auto zb = z_fn(s.substr(0, m-1) + "#" + b);
    zb = vector<int>(zb.begin()+m, zb.end());
    reverse(zb.begin(), zb.end());

    // res = sum_i sum_{i <= j < i+m-1} max(0, za[i]+zb[j] - m + 1)
    // => ? * (za[i]+1) - \sum (m-zb[j])
    // i.e. only (m-zb) <= za+1, contribution, count its cnt & sum.
    Fenwick<int> occur(m);
    Fenwick<ll> sum(m);
    ll res = 0;
    for (int i = 0, j = 0; i < n; i++) {
        while (j < n && j < i+m-1) {
            int p = m - zb[j];
            occur.add(p, 1);
            sum.add(p, p);
            j++;
        }
        int p = za[i] + 1;
        res += p *1ll* occur.query(p) - sum.query(p);

        p = m - zb[i];
        occur.add(p, -1);
        sum.add(p, -p);
    }
    cout << res;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}
