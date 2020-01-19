#include <bits/stdc++.h>

using namespace std;

int need[] = {119, 23, 5, 1, 1, 1};
void solve() {
    vector<int> id(119);
    iota(id.begin(), id.end(), 0);
    vector<int> res(5);
    for (int i = 0; i < 5; i++) {
        vector<vector<int>> g(5);
        for (int k: id) {
            cout << k*5+i+1 << endl;
            char c; cin >> c;
            g[c-'A'].push_back(k);
        }
        for (int j = 0; j < 5; j++) {
            if (g[j].size() == need[i+1]) {
                res[i] = j;
                id = g[j];
                break;
            }
        }
    }
    // so many miswritings
    swap(res[3], res[4]);
    // ..
    for (int x:res)cout << char('A'+x);
    cout << endl;
}

// keep in mind what format needed!! might WA!
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int T; cin >> T;
    int _F; cin >> _F;
    for (int t = 1; t <= T; t++) {
        solve();
        // now char verdict...
        char verdict; cin >> verdict;
        assert(verdict == 'Y');
    }
    return 0;
}
