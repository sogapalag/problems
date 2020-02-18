#include <bits/stdc++.h>

using namespace std;

template <typename T=int>
struct Compress {
    unordered_map<T, int> id;
    vector<T> num;

    inline int get_id(T x) {
        if (!id.count(x)) {
            id[x] = num.size();
            num.emplace_back(x);
        }
        return id[x];
    }
    inline T get_num(int i) {
        assert(0 <= i && i < num.size());
        return num[i];
    }
};
template <typename T>
struct FrontVector {
    vector<T> a;
    FrontVector() {}
    FrontVector(int n, const T& x = T()) : a(n, x) {}

    void push_front(T x) {
        a.push_back(x);
    }
    void pop_front() {
        a.pop_back();
    }
    T& front() {
        return a.back();
    }
    bool empty() const {
        return a.empty();
    }
    size_t size() { return a.size(); }
    T& operator[](size_t i){
        return a[size()-i-1];
    }
};

struct Tree {
    int n;
    vector<vector<int>> g;
    vector<int> sz, pa, depth, sta, fin, tour, a, arm;
    vector<FrontVector<unordered_set<int>>> st;
    int tim;
    Tree(int _n) : n(_n)
        , g(n)
        , sz(n)
        , pa(n, -1)
        , depth(n)
        , sta(n)
        , fin(n)
        , a(n)
        , arm(n)
        , st(n)
        {
        tour.reserve(n);
        input(); 
        tim = 0; //basic_dfs(root);
        for (int r: roots) basic_dfs(r);
    }

    inline void add(int u, int v) {
        g[u].emplace_back(v);
        //g[v].emplace_back(u);
    }
    vector<int> roots; // could forest
    void input() {
        Compress<string> cs;
        for (int i = 0; i < n; i++) {
            string s; cin >> s;
            a[i] = cs.get_id(s);
            int x; cin >> x; x--;
            if (x != -1) g[x].push_back(i);
            else roots.push_back(i);;
        }
        if(0)for (int _ = 1; _ < n; _++) {
            int x,y;
            cin >> x >> y;
            --x; --y; // to 0-based
            add(x,y);
        }
    }
    void basic_dfs(int u) {
        //if (pa[u] != -1) g[u].erase(find(g[u].begin(), g[u].end(), pa[u]));
        sta[u] = tim++;
        tour.emplace_back(u);
        for (int& v: g[u]) {
            pa[v] = u;
            depth[v] = depth[u] + 1;
            basic_dfs(v);
            arm[u] = max(arm[u], arm[v] + 1);
            sz[u] += sz[v];
            // skew; should arm
            // if (depth[v] > depth[g[u][0]]) swap(v, g[u][0]);
            if (arm[v] > arm[g[u][0]]) swap(v, g[u][0]);
        }
        ++sz[u];
        fin[u] = tim;
    }

    vector<vector<pair<int,int>>> qrs;
    vector<int> res;
    void dfs(int u) {
        for (int v: g[u]) {
            dfs(v);
            if (v == g[u][0]) {
                st[u] = move(st[v]);
            } else {
                int m = st[v].size();
                for (int _ = 0; _ < m; _++) {
                    for (auto& x: st[v][_]) {
                        st[u][_].insert(x);
                    }
                }
            }
        }
        st[u].push_front({a[u]});
        for (auto& _: qrs[u]) {
            int k,i;
            tie(k,i) = _;
            if (k < st[u].size()) {
                res[i] = st[u][k].size();
            }
        }
    }
    void solve() {
        int q; cin >> q;
        qrs.resize(n);
        res.resize(q);
        for (int i = 0; i < q; i++) {
            int u, k;
            cin >> u >> k; u--;
            qrs[u].emplace_back(k, i);
        }
        for (int r: roots) dfs(r);
        for (auto& x: res) {
            cout << x << '\n';
        }
    }
};

void solve() {
    int n; cin >> n;
    Tree tr(n); tr.solve();
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}
