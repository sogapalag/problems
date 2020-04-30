#include <bits/stdc++.h>

using namespace std;


// it's trivial(only valuable intuition) to pick min likelihood
void solve() {
    int n; cin >> n;
    vector<int> likelihood(n);
    vector<bool> sold(n);
    for (int _ = 0; _ < n; _++) {
        int m; cin >> m;
        vector<int> a(m);
        for (auto& x: a) {
            cin >> x;
            likelihood[x]++;
        }
        int i = -1, mi = n;
        for (int x:a)if(!sold[x]){
            if (likelihood[x] < mi) {
                mi = likelihood[x];
                i = x;
            }
        }
        if (i != -1) sold[i] = true;
        cout << i << endl;
    }
}

// keep in mind what format needed!! might WA!
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int T; cin >> T;
    for (int t = 1; t <= T; t++) {
        solve();
        //int verdict; cin >> verdict;
        //assert(verdict == 1);
    }
    return 0;
}
