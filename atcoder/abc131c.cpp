#include <bits/stdc++.h>

using namespace std;


void solve() {
    long long a, b, c, d;
    cin >> a >> b >> c >> d;
    long long g = __gcd(c, d);
    long long l = c*d/g;
    auto f = [&](long long x){
        return x - (x/c + x/d - x/l);
    };
    cout << f(b) - f(a-1);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
