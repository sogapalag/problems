#include <bits/stdc++.h>

using namespace std;


// a[0], a[1] must choose one, neither choosing is impossible.
// then another two at most, greedy is optimal.
void solve() {
    int n; cin >> n;
    vector<int> a(n);
    for (auto& x: a) {
        cin >> x;
    }
    sort(a.begin(), a.end());
    a.erase(unique(a.begin(), a.end()), a.end());
    reverse(a.begin(), a.end());
    int m = a.size();
    auto fil = [&](vector<int>& b, int x){
        for (int i = x; i < m; i++) {
            bool T = true;
            for (auto& y: b) {
                T &= (y % a[i] != 0);
            }
            if (T) b.push_back(a[i]);
            if (b.size() == 3) break;
        }
    };
    if (m < 2) {
        cout << a[0] << "\n";
        return;
    }
    vector<int> res = {a[0]};
    fil(res, 1);
    vector<int> ans = {a[1]};
    fil(ans, 2);
    int sum = 0, tmp = 0;
    for (auto& x: res) {
        sum += x;
    }
    for (auto& x: ans) {
        tmp += x;
    }
    cout << max(sum, tmp) << "\n";
  //  int res = a[0];
  //  if (m > 1) {
  //      int tmp;
  //      if (a[0] % a[1] != 0) {
  //          tmp = a[0] + a[1];
  //          for (int i = 2; i < m; i++) {
  //              if (a[0] % a[i] != 0) {
  //                  tmp += a[i]; break;
  //              }
  //          }
  //          cout << tmp << "\n";
  //          return;
  //      }
  //      if (m > 2 && a[1]%a[2] != 0) {
  //          tmp = a[1]+a[2];
  //          for (int i = 3; i < m; i++) {
  //              if (a[1] % a[i] != 0) {
  //                  tmp += a[i];
  //                  break;
  //              }
  //          }
  //      }
  //      int cnt = 1;

  //  }
  //  cout << res << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int t; cin >> t;
    while (t--)solve();
    cout << endl;
}
