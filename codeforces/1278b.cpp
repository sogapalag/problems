#include <bits/stdc++.h>

using namespace std;
using ll=long long;

ll f(ll x){
    return x*(x+1)/2;
}

void solve() {
    int a, b;
    cin >> a >> b;
    int d = abs(a-b);
    if (d == 0) {
        cout << "0\n"; return;
    }
    ll i = 1;
    while (f(i) < d || (f(i)%2 != d%2)) {
        i++;
    }
    cout << i << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int t; cin >> t;
    while(t--)solve();
    cout << endl;
}
