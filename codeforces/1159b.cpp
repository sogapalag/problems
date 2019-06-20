#include <bits/stdc++.h>

using namespace std;

void solve() {
	int n; cin >> n;
    vector<int> a(n);
    for (auto & x: a) {
        cin >> x;
    }
    int m = 0x7f3f3f3f;
    //vector<int> d(n);
    int res = 0x7f3f3f3f;
    for (int i = n-1; i >= 0; i--) {
        m = min({m, a[i], a[n-1-i]});
        //d[i] = m;
        if (i)
            res = min(res, m/i);
    }
    cout << res;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
