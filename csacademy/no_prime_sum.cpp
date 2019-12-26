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
struct Sieve {
    int sz;
    vector<bool> is;
    vector<int> prime;
    Sieve(int n = 45000):sz(n) {
        prime.reserve(n/6);
        is.assign(n+1, true);
        is[0] = is[1] = false;
        for (int p = 2; (int64_t)p*p <= n; p++) {
            if (is[p]) {
                for (int i = p*p; i <= n; i += p) {
                    is[i] = false;
                }
            }
        }
        for (int i = 2; i <= n; i++) {
            if (is[i])
                prime.emplace_back(i);
        }
    }
}s(2e5+10);
void solve() {
    int n; cin >> n;
    vector<int> odd, even;
    for (int _ = 0; _ < n; _++) {
        int x; cin >> x;
        if(x&1)odd.push_back(x);
        else even.push_back(x);
    }

    n = odd.size();
    int m = even.size();
    if (n==0||m==0) {
        cout << 0; return;
    }

    IndepSet is(n, m);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (s.is[odd[i]+even[j]]) is.add(i, j);
        }
    }

    int res = n+m - is.get_indep_set();
    vector<int> a;
    for (int i = 0; i < n; i++) {
        if (!is.L[i]) a.push_back(odd[i]);
    }
    for (int j = 0; j < m; j++) {
        if (!is.R[j]) a.push_back(even[j]);
    }
    cout << res << "\n";
    for (auto& x: a) {
        cout << x << ' ';
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
