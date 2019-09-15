#include <bits/stdc++.h>

using namespace std;


void solve() {
    int n; cin >> n;
    set<int> s;
    for (int _ = 0; _ < n; _++) {
        int x; cin >> x;
        s.insert(x);
    }
    int cnt = 0;
    while (!s.empty()) {
        int x = *s.begin();
        for (int i = 1; i <= 100; i++) {
            s.erase(i*x);
        }
        cnt++;
    }
    cout << cnt;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
