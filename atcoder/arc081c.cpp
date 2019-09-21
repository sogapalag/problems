#include <bits/stdc++.h>

using namespace std;


void solve() {
    int n; cin >> n;
    map<int, int> cnt;
    for (int _ = 0; _ < n; _++) {
        int x; cin >> x;
        cnt[x]++;
    }
    int mx0=0, mx1=0;
    for (auto rit = cnt.rbegin(); rit != cnt.rend(); rit++) {
        if (rit->second < 2) continue;
        if (!mx0) mx0 = rit->first, rit->second-=2;
        if (rit->second < 2) continue;
        if (!mx1) {mx1 = rit->first; break;}
    }
    long long res = 1ll*mx0*mx1;
    cout << res;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
