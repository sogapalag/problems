#include <bits/stdc++.h>

using namespace std;


void solve() {
    int n,m;
    cin >> n >> m;
    vector<int> cnt(n+1);
    for (int _ = 0; _ < m; _++) {
        int x,y;
        cin >> x >> y;
        if (x==1) cnt[y]++;
        if (y==n) cnt[x]++;
    }
    for (int i = 2; i < n; i++) {
        if (cnt[i] == 2){
            cout << "POSSIBLE";
            return;
        }
    }
    cout << "IMPOSSIBLE";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
