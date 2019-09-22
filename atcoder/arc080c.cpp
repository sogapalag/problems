#include <bits/stdc++.h>

using namespace std;


void solve() {
    int n; cin >> n;
    int cnt[3] = {};
    for (int _ = 0; _ < n; _++) {
        int x; cin >> x;
        if ((x&3) == 0) cnt[2]++;
        if ((x&3) == 2) cnt[1]++;
        if ((x&1) == 1) cnt[0]++;
    }
    if (cnt[0] == 0) {
        cout << "Yes"; return;
    }
    if (cnt[1]) cnt[0]++;
    if (cnt[2] >= cnt[0]-1) {
        cout << "Yes";
    } else {
        cout << "No";
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
