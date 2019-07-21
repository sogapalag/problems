#include <bits/stdc++.h>

using namespace std;


void solve() {
    int n; cin >> n;
    vector<int> a(n);
    for (auto& x: a) {
        cin >> x;
    }
    sort(a.begin(), a.end());
    set<int> res;
    auto check = [&](int d, int i, int skip){
        int cnt = 0;
        int j = i-1;
        while (i < n) {
            if (a[i] - a[j] != d) {
                i++;
                cnt++;
            }else{
                i++;
                j = i-1;
            }
            if (cnt > skip) return;
        }
        res.insert(d);
    };
    check(a[1]-a[0], 2, 1);
    check(a[2]-a[0], 3, 0);
    check(a[2]-a[1], 3, 0);
    set<int> ans;
    for (auto& x: res) {
        if (x==0){
            ans.insert(0);
        }else{
            for (int d = 1; d*d <= x; d++) {
                if (x%d) continue;
                ans.insert(d);
                ans.insert(x/d);
            }
        }
    }
    for (auto& x: ans) {
        cout << x << "\n";
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
