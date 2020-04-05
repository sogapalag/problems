#include <bits/stdc++.h>

using namespace std;

const int N = 111; 
int a[N][N];
void solve() {
    int n; cin >> n;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> a[i][j];
        }
    }
    int k = 0, r = 0, c = 0;
    for (int i = 0; i < n; i++) {
        k += a[i][i];
    }
    for (int i = 0; i < n; i++) {
        vector<int> b;
        for (int j = 0; j < n; j++) {
            b.push_back(a[i][j]);
        }
        sort(b.begin(), b.end());
        b.erase(unique(b.begin(), b.end()), b.end());
        if (b.size() < n) r++;
    }
    for (int j = 0; j < n; j++) {
        vector<int> b;
        for (int i = 0; i < n; i++) {
            b.push_back(a[i][j]);
        }
        sort(b.begin(), b.end());
        b.erase(unique(b.begin(), b.end()), b.end());
        if (b.size() < n) c++;
    }
    cout << k << ' '<< r << ' ' << c << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int T; cin >> T;
    for (int t = 1; t <= T; t++) {
        cout << "Case #" << t << ": ";
        solve();
    }
    return 0;
}
