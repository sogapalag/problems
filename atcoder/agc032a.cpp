#include <bits/stdc++.h>

using namespace std;


// time-reverse, can only pick right-most sat.
void solve() {
    int n; cin >> n;
    vector<int> b(n);
    for (auto& x: b) {
        cin >> x;
    }
    vector<int> a;
    while (!b.empty()) {
        int sz = b.size();
        bool flag = false;
        for (int i = sz-1; i >= 0; i--) {
            if (b[i] == i+1) {
                flag = true;
                a.emplace_back(i+1);
                b.erase(b.begin()+i);
                break;
            }
        }
        if (!flag) {
            cout << -1 << "\n";
            exit(0);
        }
    }
    reverse(a.begin(), a.end());
    for (auto& x: a) {
        cout << x << "\n";
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
