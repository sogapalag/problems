#include <bits/stdc++.h>

using namespace std;

template <typename T=int>
struct Rmq {
    vector<T> raw;
    static const int LOG = 20;
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
        return raw[x] < raw[y] ? x : y;
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

// left-boarder range [cen-n+1, cen], where cen is min_id
// on this range, move -> right, left nodes become less, right become more. and depth too.
// so bs on that, find first left<=right
void solve() {
    int n; cin >> n;
    vector<int> a(3*n);
    for (int i = 0; i < n; i++) {
        int x; cin >> x;
        a[i] = a[i+n] = a[i+2*n] = x;
    }
    Rmq<> R(a);
    function<int(int,int)> depth = [&](int l, int r) {
        if (r-l < 1) return 0;
        if (r-l == 1) return 1;
        int c = R.query_id(l, r);
        return 1 + max(depth(l, c), depth(c+1, r));
    };

    int cen = R.query_id(n, 2*n);
    int i = bs_first<int>(cen-n+1, cen+1, [&](int i){
            return depth(i,cen) <= depth(cen+1,i+n);
            });
    int j = i-1;
    int dj = depth(j, j+n);
    int di = depth(i, i+n);
    if (dj < di) {
        cout << dj << ' ' << (j%n);
    } else {
        cout << di << ' ' << (i%n);
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
