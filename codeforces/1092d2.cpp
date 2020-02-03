#include <bits/stdc++.h>

using namespace std;

struct Dsu {
    int n;
    vector<int> p;
    vector<int> r;
    vector<int> L,R;
    vector<int> val;
    
    Dsu(int _n) { n = _n; p.resize(n); r.resize(n);
        L.resize(n);
        R.resize(n);
        val.resize(n);
        init(); }
    inline void init() {
        for (int i = 0; i < n; i++) {
            p[i] = i;
            r[i] = 1;
            L[i] = R[i] = i;
        }
    }
    inline int find(int x) {
        return p[x] == x ? x: p[x] = find(p[x]);
    }
    inline bool join(int x, int y) {
        x = find(x); y = find(y);
        if (x == y) return false;
        if (r[x] < r[y]) swap(x, y);
        p[y] = x; r[x] += r[y];
        L[x] = min(L[x], L[y]);
        R[x] = max(R[x], R[y]);
        val[x] = max(val[x], val[y]);
        return true;
    }
    inline bool check(int x, int y) {
        return find(x) == find(y);
    }
    int len(int x) {
        x = find(x);
        return R[x]-L[x]+1;
    }
    int getL(int x) {
        return L[find(x)];
    }
    int getR(int x) {
        return R[find(x)];
    }
    int getval(int x) {
        return val[find(x)];
    }
};

// a direct simulation of join adj
void solve() {
    int n; cin >> n;
    vector<int> a(n);
    for (auto& x: a) {
        cin >> x;
    }
    Dsu d(n);
    for (int i = 0; i < n; i++) {
        d.val[i] = a[i];
    }
    for (int i = 1; i < n; i++) {
        if (a[i-1] == a[i]) d.join(i-1, i);
    }
    using pi=pair<int,int>;
    priority_queue<pi,vector<pi>, greater<pi>> pq;
    for (int i = 0; i < n; i++) {
        if (d.find(i)==i) pq.emplace(a[i], i);
    }
    while (!pq.empty()) {
        int val, i;
        tie(val, i) = pq.top(); pq.pop();
        int l = d.getL(i);
        int r = d.getR(i);
        // outdated
        int new_val = d.getval(i);
        if (new_val > val) continue;

        int len = r-l+1;
            //cerr<<l<<','<<r<<'.'<<len<<' '<<val<<endl;
        if (len == n) break;
        if (len & 1) {
            //cerr<<len<<' '<<val<<endl;
            cout << "NO"; return;
        }
        int mi = 1e9;
        if (l>0) mi = min(mi, a[l-1]);
        if (r<n-1) mi = min(mi, a[r+1]);
        if (l>0 && mi == a[l-1]) d.join(l-1, i);
        if (r<n-1 && mi == a[r+1]) d.join(r+1, i);
        //pq.emplace(mi, i); // no need
    }
    cout << "YES";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}
