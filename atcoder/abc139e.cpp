#include <bits/stdc++.h>

using namespace std;


void solve() {
    int n; cin >> n;
    vector<vector<int>> a(n, vector<int> (n-1));
    for (int i = 0; i < n; i++) {
        for (int j = n-2; j >= 0; j--) {
            int x; cin >> x;
            a[i][j] = x-1;
        }
    }
    int TOT = n*(n-1)/2;
    set<int> now;
    for (int i = 0; i < n; i++) {
        now.insert(i);
    }
    int tot = TOT;
    for (int d = 1; d <= TOT; d++) {
        int cnt = 0;
        set<int> later;
        for (int i: now) {
            if (a[i].empty() || later.find(i) != later.end()) continue;
            int j = a[i].back();
            if (later.find(j)!=later.end() || a[j].empty() || a[j].back()!=i) continue;
            later.insert(i);
            later.insert(j);
            a[i].pop_back();
            a[j].pop_back();
            cnt++;
        }
        if (cnt == 0) {
            cout << -1; return;
        }
        tot -= cnt;
        if (tot == 0) {
            cout << d; return;
        }
        now = later;
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
