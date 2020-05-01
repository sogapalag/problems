#include <bits/stdc++.h>

using namespace std;

#define l first
#define r second
void __solve() {
    int n; cin >> n;
    vector<pair<int, int>> a(n);
    for (auto& x: a) {
        cin >> x.l >> x.r;
        --x.l;--x.r;
    }
    vector<int> id(n);
    iota(id.begin(), id.end(), 0);
    sort(id.begin(), id.end(), [&](auto& u, auto& v){
        return a[u] < a[v];
    });
    auto p = id;
    auto f = [&](auto perm){
        vector<int> res(n);
        for (int i = 0; i < n; i++) {
            res[perm[i]] = i;
        }
        return res;
    };
    auto pr = [&](auto perm){
        for (auto& x: perm) {
            cout << x+1 << ' ';
        }cout << '\n';
    };
    for (int _ = 1; _ < n; _++) {
        int i = id[_-1], j = id[_];
        if (a[i].l <= _ && _ <= a[i].r
                && a[j].l <= _-1 && _-1 <= a[j].r) {
            cout << "NO\n";
            pr(f(p));
            swap(p[_-1], p[_]);
            pr(f(p)); return;
        }
    }
    cout << "YES\n";
    pr(f(p));
}

// note greedy sweep must be a valid. i.e. pick min(r)
// then if not unique, must exist a swap-adj
void solve() {
    int n; cin >> n;
    vector<pair<int, int>> a(n);
    for (auto& x: a) {
        cin >> x.l >> x.r;
        --x.l;--x.r;
    }
    vector<vector<pair<int,int>>> g(n);
    for (int i = 0; i < n; i++) {
        g[a[i].l].emplace_back(a[i].r, i);
    }
    priority_queue<pair<int,int>, vector<pair<int,int>>, greater<pair<int,int>>> hp;
    vector<int> p(n);
    for (int i = 0; i < n; i++) {
        for (auto& _: g[i]) {
            hp.push(_);
        }
        p[i] = hp.top().second; hp.pop();
    }
    auto f = [&](auto perm){
        vector<int> res(n);
        for (int i = 0; i < n; i++) {
            res[perm[i]] = i;
        }
        return res;
    };
    auto pr = [&](auto perm){
        for (auto& x: perm) {
            cout << x+1 << ' ';
        }cout << '\n';
    };
    for (int _ = 1; _ < n; _++) {
        int i = p[_-1], j = p[_];
        if (a[i].l <= _ && _ <= a[i].r
                && a[j].l <= _-1 && _-1 <= a[j].r) {
            cout << "NO\n";
            pr(f(p));
            swap(p[_-1], p[_]);
            pr(f(p)); return;
        }
    }
    cout << "YES\n";
    pr(f(p));
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}
