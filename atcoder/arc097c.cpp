#include <bits/stdc++.h>

using namespace std;


void solve() {
    string s; cin >> s;
    int k; cin >> k;
    int n = s.size();
    set<string> candi;
    for (int i = 0; i < n; i++) {
        for (int j = 1; j <= k; j++) {
            if (i+j > n) continue;
            candi.insert(s.substr(i,j));
        }
    }
    for (int i = 1; i < k; i++) {
        candi.erase(candi.begin());
    }
    auto res = *candi.begin();
    cout << res;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
