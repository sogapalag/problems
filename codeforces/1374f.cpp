#include <bits/stdc++.h>

using namespace std;

int inv(vector<int>& a) {
    int n = a.size();
    int res = 0;
    for (int i = 0; i < n; i++) {
        for (int j = i+1; j < n; j++) {
            res += a[i] > a[j];
        }
    }
    return res;
}

// first focus easy version, a is perm.
// note op don't change parity of inversion
// thus greedy put min to its pos would work a.l.a. inv even
// for array, as long as there is equal, we can always ensure \E perm even. since swap value (3,4) change the parity.
void solve() {
    int n; cin >> n;
    vector<int> a(n);
    for (auto& x: a) cin >> x;
    vector<int> id(n);
    iota(id.begin(), id.end(), 0);
    sort(id.begin(), id.end(), [&](auto& u, auto& v){
        return a[u] < a[v];
    });
    vector<int> p(n);
    for (int i = 0; i < n; i++) {
        p[id[i]] = i;
    }
    if (inv(p) & 1) {
        for (int _ = 1; _ < n; _++) {
            if (a[id[_-1]] == a[id[_]]) {
                swap(id[_-1], id[_]);
                swap(p[id[_-1]], p[id[_]]);
                break;
            }
        }
    }
    if (inv(p) & 1) {
        cout << "-1\n"; return;
    }
    auto sw = [&](int i, int j){
        swap(p[i], p[j]);
        swap(id[p[i]], id[p[j]]);
    };
    vector<int> res;
    auto op = [&](int i){
        res.push_back(i-1);
        sw(i-2,i-1);
        sw(i-2,i);
    };
    for (int x = 0; x < n; x++) {
        if (id[x] != x) {
            while (id[x] > x+1) {
                op(id[x]);
            }
            if (id[x] == x+1) {
                op(id[x]+1);
                assert(id[x] == x+2);
                op(id[x]);
            }
            assert(id[x] == x);
        }
    }
    cout << res.size() << "\n";
    for (int i:res) {
        cout << i << ' ';
    }cout << '\n';
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int T; cin >> T;
    for (int t = 0; t < T; t++) {
        solve();
    }
    return 0;
}
