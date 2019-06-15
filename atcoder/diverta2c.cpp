#include <bits/stdc++.h>

using namespace std;


void solve() {
    int n; cin >> n;
    vector<int> a(n);
    for (auto& x: a) {
        cin >> x;
    }
    sort(a.begin(), a.end());
    int i = lower_bound(a.begin(), a.end(), 0) - a.begin();
    i -= 1;
    if (a[0] >= 0) i = 0;
    if (a[n-1] <= 0) i = n-2;
    int ne = 0, po = 0;
    for (int j = 0; j < n; j++) {
        if (j <= i) ne += a[j];
        else po += a[j];
    }
    int res = po - ne;
    cout << res << "\n";

    int crt = a[i+1];
    int j = i;
    while (j > 0) {
        cout << crt << ' ' << a[j] << "\n";
        crt -= a[j];
        j--;
    }
    if (i+1 == n-1) {
        cout << crt << ' ' << a[0];
        crt -= a[0];
        assert(crt == res);
        return;
    }
    cout << a[0] << ' ' << crt << "\n";
    crt = a[0] - crt;
    j = i+2;
    while (j < n-1) {
        cout << crt << ' ' << a[j] << "\n";
        crt -= a[j];
        j++;
    }
    cout << a[n-1] << ' ' << crt << "\n";
    crt = a[n-1] - crt;
    assert(crt == res);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
