#include <bits/stdc++.h>

using namespace std;
using ll=long long;

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

void solve() {
    int n; cin >> n;
    vector<vector<int>> g(n);
    for (int _ = 1; _ < n; _++) {
        int x,y;
        cin >> x >> y;
        x--;y--;
        g[x].emplace_back(y);
        g[y].emplace_back(x);
    }

    vector<pair<ll, ll>> a(n);
    ll D = 1e7;
    ll l = 0;
    function<void(int,int)> dfs = [&](int u,int p){
        int i = 1;
        for (int v:g[u])if(v!=p){
            a[v] = {l-=D, a[u].first + (i++)};
            dfs(v,u);
        }
    };
    a[0] = {l, D};
    dfs(0, -1);
    
    vector<ll> b;
    for (int i = 0; i < n; i++) {
        b.push_back(a[i].first);
        b.push_back(a[i].second);
    }
    Compress<ll> c(b);
    for (int i = 0; i < n; i++) {
        int x = c.get_id(a[i].first) + 1;
        int y = c.get_id(a[i].second)+ 1;
        cout << x <<' '<< y << "\n";
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
