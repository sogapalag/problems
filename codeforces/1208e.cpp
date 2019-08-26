#include <bits/stdc++.h>

using namespace std;

struct Ch {
    int i, x;
    Ch() {}
    Ch(int _i, int _x): i(_i), x(_x){}
};

void solve() {
    int n, m;
    cin >> n >> m;
    vector<int> len(n);
    vector<multiset<int>> f(n);
    vector<vector<Ch>> ad(m), rm(m);
    for (int i = 0; i < n; i++) {
        int l; cin >> l;
        len[i] = l;
        for (int p = 0; p < l; p++) {
            int x; cin >> x;
            ad[p].emplace_back(i, x);
            rm[m-l+p].emplace_back(i, x);
        }
        if (l < m) {
            ad[l].emplace_back(i, 0);
            rm[m-1].emplace_back(i, 0);
            ad[0].emplace_back(i, 0);
            rm[m-1-l].emplace_back(i, 0);
        }
    }
    auto mx = [&](int i){
        return f[i].empty() ? 0 : *f[i].rbegin();
    };

    vector<long long> res(m);
    long long sum = 0;
    for (int p = 0; p < m; p++) {
        for (auto& a: ad[p]) {
            sum -= mx(a.i);
            f[a.i].insert(a.x);
            sum += mx(a.i);
        }
        res[p] = sum;
        for (auto& a: rm[p]) {
            sum -= mx(a.i);
            f[a.i].erase(f[a.i].find(a.x));
            sum += mx(a.i);
        }
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
