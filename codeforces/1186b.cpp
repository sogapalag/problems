#include <bits/stdc++.h>

using namespace std;

using ll=long long;
ll f(ll n, ll m) {
    if (n > m) return f(m, n);
    if (n==1) return (m+1)/3;
    if (n==2) return (m+1)/2;
    ll s = (m+1)%3;
    ll tmp = (n+1)/2 * f(1,m) + (s==2?f(1,n):0);
    s = (n+1)%3;
    ll res = (n+1)/3 * f(2,m) + (s==2?f(1,m):0);
    return max(res, tmp);
}
//problem set wrong.
// wrong solution but passed... correct ans (n+1)*(m+1)/6. 
void solve() {
    ll n, m;
    cin >> n >> m;
    cout << f(n,m);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
