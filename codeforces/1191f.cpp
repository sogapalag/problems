#include <bits/stdc++.h>

using namespace std;
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
struct Point {
    int x, y;
    Point() {}
    Point(int _x, int _y): x(_x), y(_y) {}
};

// y dec.
// consider new (xi, y), in set, xi is smallest new xs
void solve() {
    int n; cin >> n;
    vector<int> X(n);
    vector<int> Y(n);
    for (int i = 0; i < n; i++) {
        cin >> X[i] >> Y[i];
    }
    Compress<> cx(X), cy(Y);
    vector<Point> p(n);
    for (int i = 0; i < n; i++) {
        p[i] = {cx.get_id(X[i]) + 1, cy.get_id(Y[i]) + 1};
    }
    sort(p.begin(), p.end(), [&](auto& u, auto& v){
            return u.y > v.y || (u.y==v.y && u.x < v.x);
            });
    Fenwick<> f(n);
    int i = 0;
    long long res = 0;
    while (i < n) {
        int j = i;
        while (j < n && p[j].y == p[i].y) {
            int x = p[j].x;
            if (f.query(x, x) == 0) {
                f.add(x, 1);
            }
            j++;
        }
        int las = 0;
        for (int k = i; k < j; k++) {
            int x = p[k].x;
            res += 1ll*f.query(las+1, x)*f.query(x, n);
            las = x;
        }
        i = j;
    }
    cout << res;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
