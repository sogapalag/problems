#include <bits/stdc++.h>

using namespace std;


void solve() {
    int n; cin >> n;
    vector<int> a(n);
    int mx = -1e8, mi = 1e8;
    for (auto& x: a) {
        cin >> x;
        mx = max(mx, x);
        mi = min(mi, x);
    }
    vector<pair<int, int>> res;
    auto pos = [&](){
        for (int i = 1; i < n; i++) {
            res.emplace_back(i,i+1);
        }
    };
    auto neg = [&](){
        for (int i = n-1; i >= 1; i--) {
            res.emplace_back(i+1, i);
        }
    };
    if (mi >= 0) pos();
    else if (mx <= 0) neg();
    else {// make all pos/neg
        if (mx >= -mi) {
            int k = max_element(a.begin(), a.end()) - a.begin();
            k++;
            for (int i = 1; i <= n; i++) {
                if (i != k) res.emplace_back(k, i);
            }
            pos();
        } else {
            int k = min_element(a.begin(), a.end()) - a.begin();
            k++;
            for (int i = 1; i <= n; i++) {
                if (i != k) res.emplace_back(k, i);
            }
            neg();
        }
    }
    cout << res.size() << "\n";
    for (auto& p: res) {
        int x,y;
        tie(x,y) = p;
        cout << x << ' ' << y << "\n";
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
