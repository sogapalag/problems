#include <bits/stdc++.h>

using namespace std;
using vi = vector<int> ;

// when range [l, r), has property notP~P, want first P.
// when return r, means not found.
template <typename T>
T bs_first(T l, T r, function<bool (T)> f) {
    assert(l < r);
    T mid;
    while (l != r) {
        mid = l + (r-l)/2;
        if (f(mid)) {
            r = mid;
        }else {
            l = mid + 1;
        }
    }
    return r;
}

void solve() {
    int n; cin >> n;
    auto q = [&](int r, vi T, int v){
        cout << "1\n";
        cout << r << "\n";
        cout << T.size() << "\n";
        for (auto& x: T) {
            cout << x << ' ';
        }cout << "\n";
        cout << v << endl;

        cin >> r; return r;
    };
    vector<int> sz(n+1);
    vector<int> tmp;
    for (int i = 2; i <= n; i++) {
        tmp.push_back(i);
    }
    for (int i = 2; i <= n; i++) {
        sz[i] = q(1, tmp, i);
    }
    sz[1] = n;
    vector<int> id(n);
    iota(id.begin(), id.end(), 1);
    sort(id.begin(), id.end(), [&](auto& u, auto& v){
        return sz[u] < sz[v];
    });

    vector<pair<int, int>> res;
    vector<int> yasuo; // v, not found parent yet
    for (int u: id) {
        if (sz[u] == 1) yasuo.push_back(u);
        else if (u != 1){
            int sum = sz[u] - 1;
            while (sum > 0) {
                int m = yasuo.size();
                int i = bs_first<int>(0, m, [&](int i){
                        vector<int> pref;
                        for (int _ = 0; _ <= i; _++) {
                            pref.push_back(yasuo[_]);
                        }
                        return q(1, pref, u) > 0;
                        });
                res.emplace_back(u, yasuo[i]);
                sum -= sz[yasuo[i]];
                swap(yasuo[i], yasuo[m-1]);
                yasuo.pop_back();
            }
            yasuo.push_back(u);
        }
    }
    for (int u: yasuo) res.emplace_back(1, u);

    cout << "ANSWER\n";
    for (auto& _: res) {
        int x,y;
        tie(x,y)=_;
        cout << x << ' ' << y << "\n";
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
