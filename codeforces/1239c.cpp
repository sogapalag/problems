#include <bits/stdc++.h>

using namespace std;
using ll=long long;

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

struct Node {
    int i, t;
    Node() {}
    Node(int _i, int _t) : i(_i), t(_t) {}
    bool operator<(const Node& _oth) const {
        return t < _oth.t || (t == _oth.t && i < _oth.i);
    }
};

void solve() {
    int n; ll T;
    cin >> n >> T;
    vector<Node> a(n);
    for (int i = 0; i < n; i++) {
        int t; cin >> t;
        a[i] = {i, t};
    }
    sort(a.begin(), a.end());
    queue<int> q;
    set<int> r;
    ll now = 0;
    vector<ll> res(n);
    Fenwick<> f(n);
    int i = 0;
    int last = -1;
    while (i < n) {
        while (i < n && a[i].t < now) {
            if (f.query(a[i].i) == 0) {
                q.push(a[i].i);
            } else {
                r.insert(a[i].i);
            }
            f.add(a[i].i + 1, 1);
            i++;
        }
        if (last != -1) f.add(last+1, -1);
        while (i < n && a[i].t == now) {
            if (f.query(a[i].i) == 0) {
                q.push(a[i].i);
            } else {
                r.insert(a[i].i);
            }
            f.add(a[i].i + 1, 1);
            i++;
        }
        if (q.empty()) {
            if (r.empty()) {
                now = a[i].t;
                continue;
            } else {
                q.push(*r.begin());
                r.erase(r.begin());
            }
        }
        int k = q.front(); q.pop();
        res[k] = now += T;// f.add(k+1, -1);
        last = k;

    }
    while (!q.empty()) {
        int k = q.front(); q.pop();
        res[k] = now += T;
    }
    while (!r.empty()) {
        int k = *r.begin();
        r.erase(r.begin());
        res[k] = now += T;
    }
    for (auto& x: res) {
        cout << x << ' ';
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
