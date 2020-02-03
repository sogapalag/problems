#include <bits/stdc++.h>

using namespace std;


void solve() {
    int n; cin >> n;
    int mx = 0;
    vector<int> a(n);
    for (auto& x: a) {
        cin >> x;
        mx = max(mx, x);
    }
    // WA 3 1 2 4
    //for (int i = 0; i < n-1; i++) {
    //    if (a[i] > mx) { cout << "NO";return; }
    //    int d = mx - a[i];
    //    a[i] += d;
    //    a[i+1] += d;
    //}
    //cout << (a[n-1]==mx ? "YES" : "NO");

    vector<int> stk;
    for (int x: a) {
        if (!stk.empty() && stk.back() == x) {
            stk.pop_back(); //pair-up
        } else if (stk.empty() || stk.back() > x) {
            stk.push_back(x);
        } else {// back-part no way out
            cout << "NO"; return;
        }
    }
    bool yes = stk.empty() || stk.back()==mx;
    cout << (yes?"YES":"NO");
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}
