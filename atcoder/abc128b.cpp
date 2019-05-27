#include <bits/stdc++.h>

using namespace std;


void solve() {
    int n; cin >> n;
    struct Node {
        string s;
        int p;
    };
    vector<Node> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i].s;
        cin >> a[i].p;
    }
    vector<int> id(n);
    iota(id.begin(), id.end(), 0);
    sort(id.begin(), id.end(), [&](int x, int y){
            if (a[x].s < a[y].s) return true;
            if (a[x].s == a[y].s && a[x].p > a[y].p) return true;
            return false;
            });
    for (int i: id) {
        cout << i+1 << "\n";
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
