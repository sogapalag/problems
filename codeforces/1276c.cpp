#include <bits/stdc++.h>

using namespace std;


void solve() {
    int n; cin >> n;
    vector<int> a(n);
    unordered_map<int, int> mp;
    for (int i = 0; i < n; i++) {
        int x; cin >> x;
        mp[x]++;
        a[i] = x;
    }
    map<int, vector<int>> by_sz;
    vector<int> h(n+1);
    for (auto& p: mp) {
        h[p.second]++;
        by_sz[p.second].push_back(p.first);
    }
    vector<int> sum(n+1);
    for (int i = 1; i <= n; i++) {
        sum[i] = sum[i-1] + h[i]*i;
    }
    vector<int> suf_occur(n+1);
    for (int i = n; i >= 1; i--) {
        suf_occur[i-1] = suf_occur[i] + h[i];
    }

    int sz = 0, p,q;
    for (int i = 1; i*i <= n; i++) {
        int has = sum[i] + suf_occur[i]*i;
        has -= has%i;
        if (has/i < i) continue;
        if (has > sz) {
            sz = has;
            p = i; q = sz/i;
        }
    }

    vector<int> b;
    //for (auto& _: mp) {
    //    int x = min(_.second, p);
    //    for (int i = 0; i < x; i++) {
    //        b.push_back(_.first);
    //    }
    //}
    // need to process cnt=p first, otherwise, pattern could in same col
    for (auto rit = by_sz.rbegin(); rit != by_sz.rend(); rit++) {
        int y = min(rit->first, p);
        for (auto& x: rit->second) {
            for (int i = 0; i < y; i++) {
                b.push_back(x);
            }
        }
    }
    assert((int)b.size() >= sz);
    vector<vector<int>> g(p, vector<int>(q));
    int c = 0;
    for (int j = 0; j < q; j++) {
        for (int i = 0; i < p; i++) {
            g[i][(j+i)%q] = b[c++];
        }
    }
    cout << sz << "\n";
    cout << p <<' '<<q<< "\n";
    for (int i = 0; i < p; i++) {
        for (int j = 0; j < q; j++) {
            cout << g[i][j] << ' ';
        }cout << "\n";
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
