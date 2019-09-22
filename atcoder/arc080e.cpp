#include <bits/stdc++.h>

using namespace std;

template <typename T=int>
struct Rmq {
    vector<T> raw;
    static const int LOG = 18; // 20;
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

    vector<Rmq<>> R;

struct Node {
    int l, r;
    bool c;
    Node() {}
    Node(int _l, int _r, bool _c) : l(_l), r(_r), c(_c) {}
    inline int eval_id() {
        return R[c].query_id(l,r);
    }
    inline int eval() const{
        return R[c].query(l,r);
    }
    bool operator<(const Node& _oth) const {
        return eval() > _oth.eval();
    }
};

// by parity, pick min i, from another parity pick j min [i,r)
// cut into 3 intervals, maintain heap
void solve() {
    int n; cin >> n;
    int m = n>>1;
    vector<vector<int>> a(2,vector<int> (m));
    for (int i = 0; i < m; i++) {
        cin >> a[0][i] >> a[1][i];
    }
    R.emplace_back(a[0]);
    R.emplace_back(a[1]);
    vector<pair<int, int>> res;

    //function<void(int,int,bool)> dfs = [&](int l, int r, bool x){
    //    if (l >= r) return; 
    //    int i = R[x].query_id(l, r);
    //    int j = R[x^1].query_id(i+x, r+x);
    //    res.emplace_back(a[x][i], a[x^1][j]);
    //    dfs(l, i, x);
    //    dfs(i+x, j, x^1);
    //    dfs(j+(x^1), r, x);
    //};
    //dfs(0, m, 0);
    //sort(res.begin(), res.end());

    // draw clear graph, to consistent c^1 +c +.x&*#@(&#)
    priority_queue<Node> pq;
    pq.push({0, m, 0});
    while (!pq.empty()) {
        auto u = pq.top(); pq.pop();
        int l=u.l,r=u.r,c=u.c;
        int i = u.eval_id();
        int j = R[c^1].query_id(i+c, r+c);
        res.emplace_back(a[c][i], a[c^1][j]);
        if (l < i) pq.push({l,i,c});
        i += c;
        if (i < j) pq.push({i,j,c^1});
        j += c^1;
        if (j < r) pq.push({j, r, c});
    }

    for (auto& p: res) {
        cout << p.first << ' ' << p.second << ' ';
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
