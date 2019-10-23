#include <bits/stdc++.h>

using namespace std;

const int N = 200005; 

// keep erase >k with right-most r seg.
void solve() {
    int n,k;
    cin >> n >> k;
    vector<int> l(n+1), r(n+1);
    vector<vector<int>> events(N);
    for (int i = 1; i <= n; i++) {
        cin >> l[i] >> r[i];
        events[l[i]].emplace_back(i);
        events[r[i]+1].emplace_back(-i);
    }
    set<pair<int,int>> s;
    vector<int> res;
    for (auto& es: events) {
        for (int i: es) {
            if (i > 0) {
                s.emplace(r[i], i);
            } else {
                auto it = s.find({r[-i], -i});
                if (it != s.end()) s.erase(it);
            }
        }
        while ((int)s.size() > k) {
            auto it = --s.end();
            res.emplace_back(it->second);
            s.erase(it);
        }
    }
    cout << res.size() << "\n";
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
