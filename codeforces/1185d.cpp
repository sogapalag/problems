#include <bits/stdc++.h>

using namespace std;

#define f first

void solve() {
    int n; cin >> n;
    vector<pair<int, int>> a(n);
    for (int i = 0; i < n; i++) {
        int x; cin >> x;
        a[i] = {x, i+1};
    }
    sort(a.begin(), a.end());
    if (n <= 3) {
        cout << 1; return;
    }
  //  if (d0 == d1) {
  //      int cnt = 0;
  //      int j = 2;
  //      for (int i = 3; i < n; i++) {
  //          if (a[i].f - a[j].f == d0) {
  //              j += cnt + 1;
  //          } else {
  //              if (cnt) {work =false; break;}
  //              cnt++;
  //              res = a[i].second;
  //          }
  //      }
  //      if (work) {
  //          cout << res; return;
  //      }
  //  }

    int d0 = a[1].f - a[0].f;
    int d1 = a[2].f - a[1].f;
    int res = a[0].second;
    bool work = true;
    auto check = [&](int d){
        int cnt = 0;
        int can_skip = 0;
        int j = 0;
        for (int i = 1; i < n; i++) {
            if (a[i].f - a[j].f == d) {
                j += can_skip + 1;
                can_skip = 0;
            } else {
                if (cnt) {work =false; break;}
                cnt++;
                can_skip = 1;
                res = a[i].second;
            }
        }
        if (work) {
            cout << res; return true;
        }
        return false;
    };
    if (check(d0)) return;
    work = true;
    if (check(d0+d1)) return;
    res = a[0].second;
    work = true;

        for (int i = 2; i < n; i++) {
            if (a[i].f - a[i-1].f != d1) {
                work = false;
                break;
            }
        }
        if (work) {
            cout << res; return;
        }
    cout << -1;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
