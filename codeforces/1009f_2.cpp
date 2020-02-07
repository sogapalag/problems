#include <bits/stdc++.h>

using namespace std;

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
    vector<int> sz, pa, depth, sta, fin, tour, arm;
    int tim;
    Tree(int _n) : n(_n)
        , g(n)
        //, sz(n)
        , pa(n, -1)
        , depth(n)
        //, sta(n)
        //, fin(n)
        , arm(n)
        {
        //tour.reserve(n);
        input(); 
        tim = 0; basic_dfs(0);
    }

    inline void add(int u, int v) {
        g[u].emplace_back(v);
        g[v].emplace_back(u);
    }
    void input() {
        for (int _ = 1; _ < n; _++) {
            int x,y;
            cin >> x >> y;
            --x; --y; // to 0-based
            add(x,y);
        }
    }
    void basic_dfs(int u) {
        if (pa[u] != -1) g[u].erase(find(g[u].begin(), g[u].end(), pa[u]));
        //sta[u] = tim++;
        //tour.emplace_back(u);
        for (int& v: g[u]) {
            pa[v] = u;
            depth[v] = depth[u] + 1;
            basic_dfs(v);
            arm[u] = max(arm[u], arm[v] + 1);
            //sz[u] += sz[v];
            // skew max-height
            if (arm[v] > arm[g[u][0]]) swap(v, g[u][0]);
        }
        //++sz[u];
        //fin[u] = tim;
    }

    vector<FrontVector<int>> cnt;
    vector<int> id;
    void dfs(int u) {
        bool is_first = true;
        for (int v: g[u]) {
            dfs(v);
            if (is_first) {
                cnt[u] = move(cnt[v]);
                id[u] = id[v];
                is_first = false;
            } else {
                int m1 = cnt[v].size();
                for (int i = m1-1; i >= 0; i--) {
                    cnt[u][i] += cnt[v][i];
                    if (cnt[u][i] >= cnt[u][id[u]]) {
                        id[u] = i;
                    }
                }
            }
        }
        if (!cnt[u].empty() && 1 < cnt[u][id[u]]) {
            id[u]++;
        }
        cnt[u].push_front(1);
    }
    void solve() {
        cnt.resize(n);
        id.resize(n);
        dfs(0);
        for (int x: id) cout << x << '\n';
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
