#include <bits/stdc++.h>

using namespace std;


void solve() {
    int n; cin >> n;
    deque<int> a;
    for (int i = 0; i < n; i++) {
        int x; cin >> x;
        if (i&1) a.push_back(x);
        else a.push_front(x);
    }
    if (!(n&1)) reverse(a.begin(), a.end());
    for (auto& x: a) {
        cout << x << ' ';
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
