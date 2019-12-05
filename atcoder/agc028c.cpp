#include <bits/stdc++.h>

using namespace std;
using ll=long long;

// invalid iff A_i, B_j s.t. {i..,j..} = [n] and |{i}|>0 |{j}|>0.
void solve() {
    int n; cin >> n;
    vector<pair<int, int>> a;
    for (int i = 1; i <= n; i++) {
        int x,y;
        cin >> x >> y;
        a.emplace_back(x,i);
        a.emplace_back(y,-i);
    }
    sort(a.begin(), a.end());

    vector<bool> trk(n);
    ll res = 0;
    int pos = 0, neg = 0;
    for (int i = 0; i < n; i++) {
        res += a[i].first;
        int j = a[i].second;
        trk[abs(j)-1] = true;
        j>0?pos++:neg++;
    }
    
    int cnt = 0;
    for (int x: trk) cnt+=x;
    if (cnt == n && (pos > 0 && neg > 0)) {
        int j0 = a[n-1].second, j1 = a[n].second;
        // j0!=j1, replace valid, !=[n]
        if (abs(j0) != abs(j1)) {
            res -= a[n-1].first;
            res += a[n].first;
        } else {
            j0>0?pos--:neg--;
            j1>0?pos++:neg++;
            // =[n], but full Ai or full Bj
            if (pos == n || neg == n) {
                res -= a[n-1].first;
                res += a[n].first;
            } else {
                // two possible valid replacement
                ll d0 = a[n].first - a[n-2].first;
                ll d1 = a[n+1].first - a[n-1].first;
                res += min(d0,d1);
            }
        }
    }
    cout << res;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
