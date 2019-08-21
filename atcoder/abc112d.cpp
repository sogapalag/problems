#include <bits/stdc++.h>

using namespace std;


void solve() {
    int n, m;
    cin >> n >> m;
    auto divs = [](int n){
        vector<int> res;
        for (int i = 1; i*i <= n; i++) {
            if (n % i == 0) {
                res.emplace_back(i);
                if (i*i != n)
                    res.emplace_back(n/i);
            }
        }
        sort(res.begin(), res.end(), greater<int>());
        return res;
    };
    for (int d: divs(m)) {
        if (m/d >= n) {
            cout << d;
            return;
        }
    }

}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
