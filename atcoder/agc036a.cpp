#include <bits/stdc++.h>

using namespace std;

using ll=long long ;
void solve() {
    ll S;
    cin >> S;
    const ll N = 1000'000'000;
    ll x3 = (S%N)?N-S%N:0, y2 = 1;
    ll x2 = (S+x3)/N, y3 = N;
    cout << "0 0 " << x2 << ' '<<y2<<' '<<x3<<' '<<y3;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
