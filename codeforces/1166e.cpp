#include <bits/stdc++.h>

using namespace std;


// set product of prime, for intersection point.
void solve() {
    const int N = 10004; 
    int m, n;
    cin >> m >> n;
    vector<bitset<N>> a(m);
    for (int i = 0; i < m; i++) {
        int k; cin >> k;
        for (int _ = 0; _ < k; _++) {
            int x; cin >> x;
            a[i].set(x);
        }
    }
    for (int i = 1; i < m; i++) {
        for (int j = 0; j < i; j++) {
            if ((a[i] & a[j]).none()) {
                cout << "impossible";
                return;
            }
        }
    }
    cout << "possible";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
