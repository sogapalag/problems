#include <bits/stdc++.h>

using namespace std;


void solve() {
    int n, x;
    cin >> n >> x;
    if (x >= (1<<n)) {
        int l = (1<<n) - 1;
        cout << l << "\n";;
        for (int i = 1; i < (1<<n); i++) {
            cout << (i^(i-1)) << ' ';
        }
    } else {
        int M = (1<<n);
        vector<bool> t(M);
        vector<int> a; a.reserve(M);
        for (int i = 1; i < M; i++) {
            if (i!=x && !t[i] && !t[i^x]) {
                a.emplace_back(i);
                t[i] = true;
            }
        }
        cout << a.size() << "\n";
        if (a.size() > 0) {
            cout << a[0] << ' ';
            for (int i = 1; i < a.size(); i++) {
                cout << (a[i]^a[i-1]) << ' ';
            }
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
