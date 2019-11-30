#include <bits/stdc++.h>

using namespace std;

struct Bip {
    int n,m; // #l, #r
    vector<vector<int>> g;
    vector<int> left;
    vector<bool> trk;

    Bip(int _n) : n(_n), m(_n) {
        init();
    }
    Bip(int _n, int _m) : n(_n), m(_m) {
        init();
    }
    void init() {
        g.resize(n);
        left.assign(m, -1);
        trk.assign(n, false);
    }
    inline void add(int l, int r) {
        assert(0 <= l && l < n);
        assert(0 <= r && r < m);
        g[l].emplace_back(r);
    }

    bool dfs(int l) {
        if (trk[l]) return false;
        trk[l] = true;
        for (int r: g[l]) {
            if (left[r] == -1 || dfs(left[r])) {
                left[r] = l;
                return true;
            }
        }
        return false;
    }
    int match() {
        int cnt = 0;
        for (int i = 0; i < n; i++) {
            fill(trk.begin(), trk.end(), false);
            if (dfs(i)) cnt++;
        }
        return cnt;
    }
};

// true, means in IndepSet
// otherwise, in VertexCover
struct IndepSet : Bip {
    vector<bool> L,R;

    IndepSet(int _n) : Bip(_n), L(n, false), R(m, true) {}
    IndepSet(int _n, int _m) : Bip(_n,_m), L(n, false), R(m, true) {}

    void dfs_set(int l) {
        L[l] = true;
        for (int r: g[l]) {
            if (left[r] != -1 && !L[left[r]]) {
                R[r] = false;
                dfs_set(left[r]);
            }
        }
    }

    int get_indep_set() {
        int vertex_cover = match();
        vector<int> right(n, -1);
        for (int r = 0; r < m; r++) {
            if (left[r] != -1) {
                right[left[r]] = r;
            }
        }
        for (int l = 0; l < n; l++) {
            if (right[l] == -1 && !L[l]) {
                dfs_set(l);
            }
        }
        int indep_set = 0;
        for (bool l: L) indep_set += l;
        for (bool r: R) indep_set += r;
        assert(indep_set + vertex_cover == n + m);
        return indep_set;
    }
};

struct Seg {
    int x, l, r;
    Seg() {}
    Seg(int _x, int _l, int _r) : x(_x), l(_l), r(_r) {}
};

// consider shape
//   + +
// +     +
//   + +
// two seg-set V,H. decide choose some to erase. to make all intersects dispear(covered).
// aka seg-erase = vertex cover, remain = indep set
void solve() {
    int n; cin >> n;
    vector<pair<int, int>> a(n);
    vector<int> X(n),Y(n);
    for (int i = 0; i < n; i++) {
        cin >> X[i] >> Y[i];
        a[i] = {X[i], Y[i]};
    }
    sort(X.begin(), X.end());
    X.erase(unique(X.begin(), X.end()), X.end());
    sort(Y.begin(), Y.end());
    Y.erase(unique(Y.begin(), Y.end()), Y.end());

    sort(a.begin(), a.end());
    vector<Seg> v;
    for (int i = 1; i < n; i++) {
        if (a[i].first == a[i-1].first) {
            v.emplace_back(a[i].first, a[i-1].second, a[i].second);
        }
    }
    auto b = a;
    for (auto& p: a) {
        swap(p.first, p.second);
    }
    sort(a.begin(), a.end());
    vector<Seg> h;
    for (int i = 1; i < n; i++) {
        if (a[i].first == a[i-1].first) {
            h.emplace_back(a[i].first, a[i-1].second, a[i].second);
        }
    }

    auto intersect = [](Seg& s0, Seg& s1){
        return s1.l<s0.x && s0.x<s1.r && s0.l<s1.x && s1.x<s0.r;
    };

    IndepSet bip(v.size(), h.size());
    for (int i = 0; i < (int)v.size(); i++) {
        for (int j = 0; j < (int)h.size(); j++) {
            if (intersect(v[i], h[j])) {
                bip.add(i,j);
            }
        }
    }
    bip.get_indep_set();
    auto& vis = bip.L;
    auto& his = bip.R;
    vector<Seg> resh, resv;
    int x, l, r, k = 0; // k seg id, follow previous order
    x = a[0].first;
    l = r = a[0].second;
    for (int i = 1; i < n; i++) {
        if (a[i].first == a[i-1].first && his[k++]) {
            r = a[i].second;
        } else {
            resh.emplace_back(x,l,r);
            x = a[i].first;
            l = r = a[i].second;
        }
    }resh.emplace_back(x,l,r);

    x = b[0].first;
    l = r = b[0].second; k = 0;
    for (int i = 1; i < n; i++) {
        if (b[i].first == b[i-1].first && vis[k++]) {
            r = b[i].second;
        } else {
            resv.emplace_back(x,l,r);
            x = b[i].first;
            l = r = b[i].second;
        }
    }resv.emplace_back(x,l,r);

    cout << resh.size() << "\n";
    for (auto& s: resh) {
        cout << s.l << ' ' << s.x <<' '<< s.r <<' '<< s.x << "\n";
    }
    cout << resv.size() << "\n";
    for (auto& s: resv) {
        cout << s.x << ' ' << s.l <<' '<< s.x <<' '<< s.r << "\n";
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
