#include <bits/stdc++.h>

using namespace std;


void solve() {
    int n,k,q;
    cin >> n >> k >> q;
    vector<int> a(n,k-q);
    for (int _ = 0; _ < q; _++) {
        int x; cin >> x;
        a[x-1]++;
    }
    for (int x: a){
        cout << (x>0?"Yes":"No") << "\n";
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
