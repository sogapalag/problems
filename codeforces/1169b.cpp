#include <bits/stdc++.h>

using namespace std;


void solve() {
    int n, m;
    cin >> n >> m;
    vector<int> a(m);
    vector<int> b(m);
    for (int i = 0; i < m; i++) {
        cin >> a[i] >> b[i];
    }
    set<int> x;
    function<void (int)> dfs = [&](int i){
        if (x.find(a[i])==x.end() && x.find(b[i]) ==x.end()) {
            if (x.size()==2) return;
            if (i==m-1) {
                cout << "YES" << endl; exit(0);
            }
            x.insert(a[i]);
            dfs(i+1);
            x.erase(a[i]);
            x.insert(b[i]);
            dfs(i+1);
            x.erase(b[i]);
        } else {
            if (i==m-1) {
                cout << "YES" << endl; exit(0);
            }
            dfs(i+1);
        }
    };
    dfs(0);
    cout << "NO";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
