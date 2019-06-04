#include <bits/stdc++.h>

using namespace std;


void solve() {
    int n; cin >> n;
    vector<int> a(n+1, 0);
    auto sieve = [&](){
        int cnt = 1;
        for (int p = 2; p <= n; p++) {
            if (!a[p]) {
                a[p] = cnt;
                for (long long i = 1ll*p*p; i <= n; i+=p) {
                    a[i] = cnt;
                }
                cnt++;
            }
        }
    };
    sieve();
    for (int i = 2; i <= n; i++) {
        cout << a[i] << ' ';
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
