#include <bits/stdc++.h>

using namespace std;


void solve() {
    int a,b,n;
    cin >> a >> b >> n;
    int res[] = {a,b,a^b};
    cout << res[n%3] << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int t; cin >> t;
    while(t--)solve();
    cout << endl;
}
