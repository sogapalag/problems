#include <bits/stdc++.h>

using namespace std;


// 1 33 7..7 33...3 7
void solve() {
    int n; cin >> n;
    int k = 2;
    while (k*(k-1)/2 <= n) {
        k++;
    }
    k--;

    int rem = n - k*(k-1)/2;

    cout << "133";
    for (int _ = 0; _ < rem; _++) {
        cout << "7";
    }
    for (int i = 2; i < k; i++) {
        cout << "3";
    }
    cout << "7";
    cout << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int t; cin >> t;
    while(t--)solve();
    cout << endl;
}
