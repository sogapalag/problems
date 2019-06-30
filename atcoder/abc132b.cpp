#include <bits/stdc++.h>

using namespace std;


void solve() {
    int n;
    cin >> n;
    vector<int> a(n);
    for (auto& x: a) {
        cin >> x;
    }
    int res = 0;
    for (int i = 1; i < n-1; i++) {
        if (a[i-1]>a[i] && a[i]>a[i+1]) res++;
        if (a[i-1]<a[i] && a[i]<a[i+1]) res++;
    }
    cout << res;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
