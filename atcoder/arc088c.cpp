#include <bits/stdc++.h>

using namespace std;


void solve() {
    long long x,y;
    cin >> x >> y;
    int e = 0;
    while (x <= y) {
        x<<=1;
        e++;
    }
    cout << e;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
