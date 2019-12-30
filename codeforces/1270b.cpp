#include <bits/stdc++.h>

using namespace std;


void solve() {
    int n; cin >> n;
    vector<int> a(n);
    for (auto& x: a) {
        cin >> x;
    }
    int i=1;
    for (; i < n; i++) {
        if (abs(a[i-1]-a[i]) > 1) {
            break;
        }
    }
    if (i==n)
        cout << "NO\n";
    else {
        cout << "YES\n";
        cout << i << ' '<<(i+1) <<"\n";
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int t; cin >> t;
    while(t--)solve();
    cout << endl;
}
