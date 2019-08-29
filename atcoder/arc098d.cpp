#include <bits/stdc++.h>

using namespace std;


// for each bit, at most 1 setted
void solve() {
    int n; cin >> n;
    vector<int> a(n);
    for (auto& x: a) {
        cin >> x;
    }
    vector<int> las(20,-1);
    long long res = 0;
    int l = 0;
    for (int r = 0; r < n; r++) {
        int x = a[r];
        for (int i = 0; i < 20; i++) {
            if (x & (1<<i)) {
                l = max(l, las[i]+1);
                las[i] = r;
            }
        }
        res += r-l+1;
    }
    cout << res;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
