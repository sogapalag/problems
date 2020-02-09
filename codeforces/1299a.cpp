#include <bits/stdc++.h>

using namespace std;


// only 1 0 0..0 0 =>1
void solve() {
    int n; cin >> n;
    vector<int> a(n);
    for (auto& x: a) {
        cin >> x;
    }
    for (int j = 30; j >= 0; j--) {
        vector<int> s;
        for (int i = 0; i < n; i++) {
            if (a[i]>>j&1) s.push_back(i);
        }
        if (s.size() == 1) {
            swap(a[0], a[s[0]]);
            break;
        }
    }
    for (auto& x: a) {
        cout << x << ' ';
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}
