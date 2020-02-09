#include <bits/stdc++.h>

using namespace std;

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
template <typename T=int>
struct Compress {
    map<T, int> id;
    vector<T> num;

    Compress(vector<T> v) {
        sort(v.begin(), v.end());
        v.erase(unique(v.begin(), v.end()), v.end());
        num = v;
        for (int i = 0; i < (int)num.size(); i++) {
            id[num[i]] = i;
        }
    }

    inline int get_id(T x) {
        assert(id.count(x));
        return id[x];
    }
    inline T get_num(int i) {
        assert(0 <= i && i < num.size());
        return num[i];
    }
};
using ll=long double;
// can relax +-1, contribution count
void __solve() {
    int n; cin >> n;
    vector<int> Xs;
    vector<int> a(n);
    for (auto& x: a) {
        cin >> x;
        Xs.push_back(x-1);
        Xs.push_back(x);
        Xs.push_back(x+1);
    }
    Compress<> cx(Xs);
    ll res = 0;
    {
        Fenwick<> occur(cx.num.size());
        for (int i = 0; i < n; i++) {
            int x = a[i];
            int cnt = occur.query(cx.get_id(x-1)+1, cx.get_id(x+1)+1);
            res += (i-cnt) *1ll * x;
            occur.add(cx.get_id(x)+1, 1);
        }
    }
    {
        Fenwick<> occur(cx.num.size());
        for (int i = n-1; i >= 0; i--) {
            int x = a[i];
            int cnt = occur.query(cx.get_id(x-1)+1, cx.get_id(x+1)+1);
            res += -(n-i-1-cnt) *1ll * x;
            occur.add(cx.get_id(x)+1, 1);
        }
    }
    cout << fixed<<setprecision(0)<<res;
}

// elegant.
void solve() {
    int n; cin >> n;
    ll sum = 0;
    ll res = 0;
    map<int,int> cnt;
    for (int i = 0; i < n; i++) {
        int y; cin >> y;
        // all [..] y
        res += i * 1ll * y - sum;
        // cancel y-+1
        res -= cnt[y-1]; // - +1
        res += cnt[y+1]; // - -1
        //cnt[y-1]++;
        //cnt[y+1]++;
        cnt[y]++;
        sum += y;
    }
    cout << fixed<<setprecision(0)<<res;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}
