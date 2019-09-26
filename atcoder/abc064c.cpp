#include <bits/stdc++.h>

using namespace std;


void solve() {
    int n; cin >> n;
    int sup[] = {400, 800, 1200, 1600, 2000, 2400, 2800, 3200};
    int fre = 0;
    int cnt[8] = {};
    for (int _ = 0; _ < n; _++) {
        int x; cin >> x;
        for (int i = 0; i <= 8; i++) {
            if (i < 8 && x < sup[i]) {
                cnt[i]++; break;
            }
            if (i == 8) fre++;
        }
    }
    int base = 0;
    for (int i = 0; i < 8; i++) {
        base += cnt[i]>0;
    }
    cout << max(1,base) << ' ' << (base+fre);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
