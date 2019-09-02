#include <bits/stdc++.h>

using namespace std;


void solve() {
    int n; cin >> n;
    vector<int> a(n);
    for (auto& x: a) {
        cin >> x;
    }
    vector<int> id(n);
    iota(id.begin(), id.end(),0);
    sort(id.begin(), id.end(), [&](auto& u, auto& v){
        return a[u] < a[v];
    });
    vector<int> res(n);
    for (int k = 0; k < n; k++) {
        int i = id[k];
        if (k < n/2) res[i] = a[id[n/2]];
        else res[i] = a[id[n/2 -1]];
    }
    for (auto& x: res) {
        cout << x << "\n";
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
