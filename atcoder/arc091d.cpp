#include <bits/stdc++.h>

using namespace std;


void solve() {
    int n,k;
    cin >> n >> k;
    long long res = 0;
    for (int b = k+1; b <= n; b++) {
        res += 1ll*(b-k) * (n/b);
        int a = n%b;
        res += a>=k? a-k+1:0;
        res -= (k==0)?1:0;
    }
    cout << res;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
