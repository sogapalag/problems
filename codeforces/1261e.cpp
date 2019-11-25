#include <bits/stdc++.h>

using namespace std;


// 0
// 10
//  10
//   1.
//    ..
//     .0
//      1
// in some ord(dec a) fill. obvious line [1..n] cannot be same, since each row has 10 pattern 
// so for last row, if equal to some row i. then ord(dec) will deduce row i's [j]=0 will make last row [j]=1
void solve() {
    int n; cin >> n;
    vector<int> a(n);
    for (auto& x: a) {
        cin >> x;
    }
    vector<int> id(n);
    iota(id.begin(), id.end(), 0);
    sort(id.begin(), id.end(), [&](auto& u, auto& v){
        return a[u] > a[v];
    });
    vector<string> s(n+1, string(n,'0'));
    int sta = 0;
    for (int i = 0; i < n; i++) {
        int k = id[i];
        for (int j = 0; j < a[k]; j++) {
            s[(sta+j)%(n+1)][k] = '1';
        }
        sta++;
    }
    cout << n+1 << "\n";
    for (auto& x: s) {
        cout << x << "\n";
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
