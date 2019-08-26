#include <bits/stdc++.h>

using namespace std;

const int N = 1e6+10; 
int phi[N];
void pre(int n) {
    iota(phi, phi+n+1, 0);
    for (int i = 2; i <= n; i++) {
        if (phi[i] == i) {
            phi[i] = i-1;
            for (int j=2*i; j<=n; j+=i) {
                (phi[j]/=i)*=(i-1);
            }
        }
    }
}

// for a m-sides polygon, in set only if its all divisors already in. since we add those d, #final vertex cannot grow.
// so, when m add-in, vertex[1..=m] coprime to m, cannot be coverd by any d-poly. aka phi(m). asides +2
// note 2-sides means diamter which doesn't exsit. so >3 case, add phi(1,2) exactly answer.
// why sort work? since phi(m) >= phi(d)
void solve() {
    int n, k;
    cin >> n >> k;
    if (k == 1) {
        cout << 3; return;
    }
    pre(n);
    cout << phi[6] << "\n";
    sort(phi+1, phi+n+1);
    long long res = 0;
    for (int i = 1; i <= k+2; i++) {
        cout << phi[i] << "\n";
        res += phi[i];
    }
    cout << res;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
