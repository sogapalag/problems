#include <bits/stdc++.h>

using namespace std;

struct Dsu {
    int n;
    vector<int> p;
    
    Dsu(int _n) { n = _n; p.resize(n); init(); }
    inline void init() {
        for (int i = 0; i < n; i++) {
            p[i] = i;
        }
    }
    inline int find(int x) {
        return p[x] == x ? x: p[x] = find(p[x]);
    }
    inline bool join(int x, int y) {
        x = find(x); y = find(y);
        if (x == y) return false;
        p[y] = x; return true;
    }
    inline bool check(int x, int y) {
        return find(x) == find(y);
    }
};

template <typename T=int>
struct Slider {
    vector<T> a;
    int n, d;
    deque<int> mi, mx;

    vector<int> lid, hid;

    Slider(vector<T> _a, int _d) : a(_a), d(_d) {
        n = a.size();
        lid.resize(n + d);
        hid.resize(n + d);
        build();
    }
    void build() {
        for (int i = 0; i < n+d-1; i++) {
            while (i < n && !mi.empty() && a[mi.back()] >= a[i]) {
                mi.pop_back();
            }
            mi.push_back(i);
            lid[i+1] = mi.front();
            if (i-d+1 >= 0 && i-d+1 == mi.front()) {
                mi.pop_front();
            }

            while (i < n && !mx.empty() && a[mx.back()] <= a[i]) {
                mx.pop_back();
            }
            mx.push_back(i);
            hid[i+1] = mx.front();
            if (i-d+1 >= 0 && i-d+1 == mx.front()) {
                mx.pop_front();
            }
        }
    }
    
    // [l, r)
    int min_id(int l, int r) {
        assert(1 <= r-l && r-l <= d);
        if (r-l < d) assert(l == 0 || r == n);
        return r < n ? lid[r] : lid[l+d];
    }
    T get_min(int l, int r) {
        return a[min_id(l,r)];
    }
    int max_id(int l, int r) {
        assert(1 <= r-l && r-l <= d);
        if (r-l < d) assert(l == 0 || r == n);
        return r < n ? hid[r] : hid[l+d];
    }
    T get_max(int l, int r) {
        return a[max_id(l,r)];
    }
};

void solve() {
    int n,K;
    cin >> n >> K;
    vector<int> a(n);
    for (auto& x: a) {
        cin >> x;
    }
    if (K == n) {
        cout << 1; return;
    }
    Dsu d(n-K+1);
    Slider<> s(a, K+1);
    // adj equiv?
    for (int i = 0; i+K+1 <= n; i++) {
        if (s.min_id(i, i+K+1) == i && s.max_id(i, i+K+1) == i+K) {
            d.join(i, i+1);
        }
    }

    vector<int> len(n);
    len[0] = 1;
    // sorted equiv
    for (int i = 1; i < n; i++) {
        if (a[i-1] < a[i]) len[i] = len[i-1] + 1;
        else len[i] = 1;
    }
    int id = -1;
    for (int i = 0; i+K <= n; i++) {
        if (len[i+K-1] >= K) {
            if (id == -1) id = i;
            else d.join(i, id);
        }
    }
    set<int> equiv;
    for (int i = 0; i+K <= n; i++) {
        equiv.insert(d.find(i));
    }
    cout << equiv.size();
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
