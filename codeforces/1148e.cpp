#include <bits/stdc++.h>

using namespace std;

void ensure(bool b) {
    if(!b) {
        cout << "NO"; exit(0);
    }
}
using pi=pair<int, int> ;
// key, delta should form correct braket seq. (())()
void solve() {
    int n; cin >> n;
    vector<pair<int, int>> a(n);
    vector<int> ts(n);
    for (int i = 0; i < n; i++) {
        int x; cin >> x;
        a[i] = {x, i};
    }
    for (auto& x: ts) {
        cin >> x;
    }
    sort(a.begin(), a.end());
    sort(ts.begin(), ts.end());
    vector<tuple<int,int,int>> res;
    vector<pair<int, int>> stk;
    for (int _ = 0; _ < n; _++) {
        int delta = ts[_] - a[_].first;
        int i = a[_].second;
        if (delta == 0) continue;
        if (delta > 0) stk.emplace_back(delta, i);
        else {
            while (delta < 0) {
                ensure(!stk.empty());
                int has,k;
                tie(has,k) = stk.back(); stk.pop_back();
                int d = min(has, -delta);
                has -= d, delta += d;
                res.emplace_back(k, i, d);
                if (has > 0) stk.emplace_back(has, k);
            }
        }
    }
    ensure(stk.empty());
    cout << "YES\n";
    cout << res.size() << "\n";
    for (auto& _: res) {
        int i,j,d;
        tie(i,j,d) = _;
        i++;j++;
        cout << i << ' ' << j << ' ' << d << "\n";
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}
