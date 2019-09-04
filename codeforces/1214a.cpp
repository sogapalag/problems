#include <bits/stdc++.h>

using namespace std;


void solve() {
    int n,d,e;
    cin >> n >> d >> e;
    e*=5;
    int res = n;
    for (int i = 0; i <= 500; i++) {
        if (n >= i*d) {
            int tmp = (n-i*d)%(d+e);
            res = min(res, tmp);
        }
        if (n >= i*e) {
            int tmp = (n-i*e)%(d+e);
            res = min(res, tmp);
        }
    }
    cout << res;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
